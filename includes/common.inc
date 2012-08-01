<?php

define("SL", "21");
define("FL", "25");

function _get_last_day($year, $month) {
  for ($day = 31; $day >= 28; $day--)
    if (checkdate($month, $day, $year))
      return (string) $day;
}

function _string_to_range($str) {
  if (!preg_match('#^(?P<year1>[1-9]\d{3})(?:(?:\.(?P<month1>0[1-9]|1[0-2]))(?:\.(?P<day1>0[1-9]|[12]\d|3[01]))?)?(?:(?:-(?P<year2>[1-9]\d{3}))(?:(?:\.(?P<month2>0[1-9]|1[0-2]))(?:\.(?P<day2>0[1-9]|[12]\d|3[01]))?)?)?$#', trim($str), $var))
    return FALSE;

  if (empty($var['year2'])) {
    $var['year2'] = $var['year1'];
    $var['month2'] = (empty($var['month1'])) ? '12' : $var['month1'];
    $var['day2'] = (empty($var['day1'])) ? _get_last_day($var['year2'], $var['month2']) : $var['day1'];
  } else {
    if (empty($var['month2'])) $var['month2'] = '12';
    if (empty($var['day2'])) $var['day2'] = _get_last_day($var['year2'], $var['month2']);
  }

  if (empty($var['month1'])) $var['month1'] = '01';
  if (empty($var['day1'])) $var['day1'] = '01';

//  $result['date1'] = $var['year1'].'-'.$var['month1'].'-'.$var['day1'].' 00:00:00';
//  $result['date2'] = $var['year2'].'-'.$var['month2'].'-'.$var['day2'].' 23:59:59';

//  return $result;
  return $var;
}

function _range_to_string($date1, $date2, $expanded = FALSE) {
  $d1 = str_replace('-', '.', substr($date1, 0, 10));
  $d2 = str_replace('-', '.', substr($date2, 0, 10));

  if ($expanded) return $d1.'-'.$d2;

  if ($d1 == $d2)
    return $d1;

  if (substr($date1, 8, 2) == '01')
    $d1 = substr($d1, 0, 7);
  if (substr($date2, 8, 2) == _get_last_day(substr($date2, 0, 4), substr($date2, 5, 2)))
    $d2 = substr($d2, 0, 7);

  if ($d1 == $d2)
    return $d1;

  if (strlen($d1) == 7 && substr($date1, 5, 2) == '01')
    $d1 = substr($d1, 0, 4);
  if (strlen($d2) == 7 && substr($date2, 5, 2) == '12')
    $d2 = substr($d2, 0, 4);

  return ($d1 == $d2) ? $d1 : $d1.'-'.$d2;
}
