/*
 * prayertimes.c
 *
 * Created: 5/18/2026 5:24:22 PM
 *  Author: Admin
 */ 

#include "prayertimes.h"

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* ===================== INTERNAL ===================== */

static double prayer_latitude;
static double prayer_longitude;
static double prayer_timezone;
static double prayer_julian;

static PrayerMethod prayer_method = METHOD_MWL;
static AsrMethod prayer_asr = ASR_SHAFII;

/* ===================== METHOD CONFIG ===================== */

typedef struct
{
  double fajr_angle;
  double isha_angle;
} MethodConfig;

static const MethodConfig method_config[] =
{
    {18.0, 17.0}, // MWL
    {19.5, 17.5}, // Egypt
    {18.5, 90.0}, // Makkah
    {18.0, 18.0}, // Karachi
    {15.0, 15.0}, // ISNA
};

/* ===================== BASIC MATH ===================== */

static double deg2rad(double d)
{
  return d * M_PI / 180.0;
}

static double rad2deg(double r)
{
  return r * 180.0 / M_PI;
}

static double dsin(double d)
{
  return sin(deg2rad(d));
}

static double dcos(double d)
{
  return cos(deg2rad(d));
}

static double dtan(double d)
{
  return tan(deg2rad(d));
}

static double darcsin(double x)
{
  return rad2deg(asin(x));
}

static double darccos(double x)
{
  return rad2deg(acos(x));
}

static double darctan2(double y, double x)
{
  return rad2deg(atan2(y, x));
}

static double darccot(double x)
{
  return rad2deg(atan(1.0 / x));
}

static double fix_angle(double a)
{
  a = a - 360.0 * floor(a / 360.0);

  if (a < 0)
    a += 360.0;

  return a;
}

static double fix_hour(double a)
{
  a = a - 24.0 * floor(a / 24.0);

  if (a < 0)
    a += 24.0;

  return a;
}

/* ===================== JULIAN ===================== */

static double prayer_julian_date(
    uint16_t year,
    uint8_t month,
    uint8_t day
)
{
  if (month <= 2)
  {
    year--;
    month += 12;
  }

  double A = floor(year / 100.0);
  double B = 2 - A + floor(A / 4.0);

  return floor(365.25 * (year + 4716))
      + floor(30.6001 * (month + 1))
      + day + B - 1524.5;
}

/* ===================== SUN POSITION ===================== */

typedef struct
{
  double declination;
  double equation;
} SunPosition;

static SunPosition sun_position(double jd)
{
  double D = jd - 2451545.0;

  double G = fix_angle(357.529 + 0.98560028 * D);

  double Q = fix_angle(280.459 + 0.98564736 * D);

  double L = fix_angle(
      Q
      + 1.915 * dsin(G)
  + 0.020 * dsin(2 * G)
  );

  double E = 23.439 - 0.00000036 * D;

  double decl =
      darcsin(dsin(E) * dsin(L));

  double RA =
      darctan2(
          dcos(E) * dsin(L),
          dcos(L)
      ) / 15.0;

  RA = fix_hour(RA);

  double eqt = Q / 15.0 - RA;

  SunPosition s;

  s.declination = decl;
  s.equation = eqt;

  return s;
}

static double equation_of_time(double jd)
{
  return sun_position(jd).equation;
}

static double sun_declination(double jd)
{
  return sun_position(jd).declination;
}

/* ===================== PRAYER CALC ===================== */

static double compute_midday(double t)
{
  double eqt =
      equation_of_time(prayer_julian + t);

  return fix_hour(12 - eqt);
}

static double compute_time(double angle, double t)
{
  double D =
      sun_declination(prayer_julian + t);

  double Z = compute_midday(t);

  double V =
      (1.0 / 15.0)
      *
      darccos(
          (
              -dsin(angle)
              - dsin(D) * dsin(prayer_latitude)
          )
          /
          (
              dcos(D)
              * dcos(prayer_latitude)
          )
      );

  return Z + (angle > 90 ? -V : V);
}

static double compute_asr(double step, double t)
{
  double D =
      sun_declination(prayer_julian + t);

  double G =
      -darccot(
          step
          + dtan(fabs(prayer_latitude - D))
      );

  return compute_time(G, t);
}

/* ===================== TIME CONVERT ===================== */

static void float_to_time(
    double value,
    PrayerTime *t
)
{
  value = fix_hour(value + 0.5 / 60.0);

  t->hour = (uint8_t)value;

  t->minute =
      (uint8_t)((value - t->hour) * 60.0);
}

/* ===================== PUBLIC API ===================== */

void prayer_set_method(PrayerMethod method)
{
  prayer_method = method;
}

void prayer_set_asr_method(AsrMethod method)
{
  prayer_asr = method;
}

void prayer_calculate(
    uint16_t year,
    uint8_t month,
    uint8_t day,
    double latitude,
    double longitude,
    double timezone,
    PrayerTime result[]
)
{
  prayer_latitude = latitude;
  prayer_longitude = longitude;
  prayer_timezone = timezone;

  prayer_julian =
      prayer_julian_date(year, month, day)
      - longitude / 360.0;

  double times[PRAYER_COUNT] =
  {
      5,
      5,
      6,
      12,
      13,
      18,
      18,
      18
  };

  double fajr_angle =
      method_config[prayer_method].fajr_angle;

  double isha_angle =
      method_config[prayer_method].isha_angle;

  times[PRAYER_FAJR] =
      compute_time(
          180.0 - fajr_angle,
          times[0] / 24.0
      );

  times[PRAYER_IMSAK] =
      times[PRAYER_FAJR] - (10.0 / 60.0);

  times[PRAYER_SUNRISE] =
      compute_time(
          180.0 - 0.833,
          times[1] / 24.0
      );

  times[PRAYER_DHUHR] =
      compute_midday(times[2] / 24.0);

  times[PRAYER_ASR] =
      compute_asr(
          prayer_asr,
          times[3] / 24.0
      );

  times[PRAYER_SUNSET] =
      compute_time(
          0.833,
          times[4] / 24.0
      );

  times[PRAYER_MAGHRIB] =
      times[PRAYER_SUNSET];

  if (isha_angle == 90.0)
  {
    times[PRAYER_ISHA] =
        times[PRAYER_MAGHRIB]
              + (90.0 / 60.0);
  }
  else
  {
    times[PRAYER_ISHA] =
        compute_time(
            isha_angle,
            times[6] / 24.0
        );
  }

  for (uint8_t i = 0; i < PRAYER_COUNT; i++)
  {
    times[i] += timezone
        - longitude / 15.0;

    float_to_time(times[i], &result[i]);
  }
}