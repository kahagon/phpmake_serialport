<?php
if ($argc != 2) {
    print 
        'Usage: php ' . basename(__FILE__) . ' port_string' . PHP_EOL .
        '    port_string     接続するポート' . PHP_EOL;
    exit (1);
}

use PHPMake\SerialPort as SerialPort;

$status = 0;
$portString = $argv[1];

$port = new SerialPort();

$data = null;
try {
    
    $port->open($portString);
    $port->setBaudRate(SerialPort::BAUD_RATE_9600)
            ->setFlowControl(SerialPort::FLOW_CONTROL_NONE)
            ->setCanonical(false)
            ->setVTime(0)
            ->setVMin(1);
    
    while($data = $port->read(256)) {
        print 'data received.' . PHP_EOL;
        if ($data == '!!!') {
            print 'exit.' . PHP_EOL;
            break;
        } else {
            var_dump($data);
            print PHP_EOL;
            $port->write($data);
        }
    }
    
} catch (Exception $e) {
    print $e->getMessage() . PHP_EOL;
    $status = 2;
}

if ($port->isOpen()) {
    $port->close();
}

exit ($status);
