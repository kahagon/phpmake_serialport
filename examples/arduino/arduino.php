<?php
/*
 * このスクリプトの実行には arduino が必要です。
 * このスクリプトと一緒にバンドルされている ardu.ino スケッチが arduino に
 * アップロードされている必要があります。
 */

if ($argc != 2) {
    $filename = basename(__FILE__);
    print <<<EOU
使い方: php $filename port
    port    arduino が接続されたポート

EOU;
    exit(1);
}

//$pins = array(chr(55), chr(56), chr(57), chr(58), chr(59), chr(60), chr(61));
$pins = array('7', '8', '9', ':', ';', '<', '=');
$port = new SerialPort($argv[1]);
$port
  ->setFlowControl(SerialPort::FLOW_CONTROL_SOFT)
  ->setBaudRate(SerialPort::BAUD_RATE_38400);

$port->setCanonical(false)
        ->setVTime(1)
        ->setVMin(0);
print 'arduino の準備を待っています ';
while ($port->read(1) != '?') print '.';
print '準備完了' . PHP_EOL;

$output = count($pins) . implode('', $pins);
$port->write($output);

$asc = true;
$sig = '1';
while(true) {
  $sig = $asc ? '1' : '0';

  foreach ($pins as $pin) {
    $port->write($sig . $pin); 
    usleep(50000);
  }

  $asc = !$asc;
}
