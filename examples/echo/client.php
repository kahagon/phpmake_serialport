<?php
if ($argc < 2) {
    print 
        'Usage: php ' . basename(__FILE__) . ' port_string [message]' . PHP_EOL .
        '    port_string     接続するポート' . PHP_EOL . 
        '    message        出力する文字列' . PHP_EOL;
    exit (1);
}

use PHPMake\SerialPort as SerialPort;

$status = 0;
$portString = $argv[1];
$message = $argc == 3 ? $argv[2] : "hello";

$port = new SerialPort();

try {
    
    $port->open($portString);
    $port->setBaudRate(SerialPort::BAUD_RATE_9600)
            ->setFlowControl(SerialPort::FLOW_CONTROL_NONE)
            ->setCanonical(false)
            ->setVTime(1)
            ->setVMin(0);
    while($port->read()) ; // void the remain data
    print $port->read($port->write($message)) . PHP_EOL;
} catch (Exception $e) {
    print $e->getMessage() . PHP_EOL;
    $status = 2;
}

if ($port->isOpen()) {
    $port->close();
}

exit ($status);
