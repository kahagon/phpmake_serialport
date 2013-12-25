<?php
if ($argc<2) {
    print 'specify port' . PHP_EOL;
    exit(1);
}

use PHPMake\SerialPort as SerialPort;

$retval = 0;
$device = $argv[1];
$baudRate = 9600;
$prompt = 'brightness>';
$port = new SerialPort();

try {
    $port->open($device);
    $port->setBaudRate($baudRate);
    $port->setFlowControl(SerialPort::FLOW_CONTROL_NONE);
    $port->setCanonical(false);
    $port->setVTime(0)->setVMin(0);

    $stdin = fopen('php://stdin', 'r');
    print $prompt;
    while (FALSE !== ($line=fgets($stdin))) {
        if (preg_match('/^(?:quit|exit)/', $line)) {
            break;
        }

        $brightness = pack('C', (int)$line);
        $port->write($brightness);
        print $prompt;
    }
    fclose($stdin);
} catch (Exception $e) {
    print 'exception occurred' . PHP_EOL;
    print $e->getMessage() . PHP_EOL;
    $retval = 2;
}

if ($port->isOpen()) {
    $port->close();
}

exit ($retval);
