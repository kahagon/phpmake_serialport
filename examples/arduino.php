<?php
/*
 * this script can run with arduino board.
 * the arduino board must be installed the sketch which is provided by ruby-serialport.
 * see https://rubygems.org/gems/serialport
 */

//$pins_asc = array(chr(55), chr(56), chr(57), chr(58), chr(59), chr(60), chr(61));
$pins_asc = array('7', '8', '9', ':', ';', '<', '=');
$pins_desc = array_reverse($pins_asc);
$port = new SerialPort('/dev/ttyUSB0');
$port->open()
  ->setFlowControl(SerialPort::FLOW_CONTROL_SOFT)
  ->setBaudRate(SerialPort::BAUD_RATE_38400);

// waiting for board ready. but this way is informal.
// formally, should read the board status.
sleep(3);

$port->write(count($pins_asc) . implode('', $pins_asc));

$asc = true;
$sig = '1';
$tmp_pins = array();
while(true) {
  if ($asc) {
    $tmp_pins = $pins_asc;
    $sig = '1';
  } else {
    //$tmp_pins = $pins_desc;
    $tmp_pins = $pins_asc;
    $sig = '0';
  }

  foreach ($tmp_pins as $pin) {
    $port->write($sig . $pin); 
    usleep(50000);
  }

  $asc = !$asc;
}
