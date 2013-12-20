<?php
if ($argc<2) {
    print 'specify port' . PHP_EOL;
    exit(1);
}

$retval = 0;
$device = $argv[1];
$baudRate = 9600;
$port = new SerialPort();

try {
    $port->open($device);
    $port->setBaudRate($baudRate);
    $port->setFlowControl(SerialPort::FLOW_CONTROL_NONE);
    $port->setCanonical(false);
    $port->setVTime(0)->setVMin(0);

    while (true) {
        $data = $port->read(256);
        print $data;
    }
} catch (Exception $e) {
    print 'exception occurred' . PHP_EOL;
    print $e->getMessage() . PHP_EOL;
    $retval = 2;
}

if ($port->isOpen()) {
    $port->close();
}

exit ($retval);
