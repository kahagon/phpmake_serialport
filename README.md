Gorilla PHPMake\SerialPort
==========================
The PHP extension for communicate other device via serial-port(COM).  
This module is Cross Platform. Gorilla able to run on POSIX system and Windows.  
You are able to talk to microcontroller(e.g. Arduino, AVR or PIC, etc) with PHP, if you use this extension.

シリアルポート(COM)を介して他のデバイスと通信を行うための PHP 拡張です。  
このモジュールは Linux などの POSIX システムと Windows で動作します。  
Gorilla を用いれば PHP で Arduino や AVR, PIC といったマイクロコントローラと通信ができます。

This is a standalone PHP extension created using CodeGen_PECL 1.1.3


BUILDING ON UNIX etc.
=====================

To compile your new extension, you will have to execute the following steps:

1.  $ ./phpize
2.  $ ./configure [--enable--Gorilla] 
3.  $ make
4.  $ make test
5.  $ [sudo] make install


BINARY(DLL) FOR WINDOWS
=======================

Building PHP extension for Windows is more hard than UNIX like platform.  
There are some binaries for Windows.  
http://sandbox.n-3.so/Gorilla/downloads/

These zip files are named with next rule.  
Gorilla-[version of Gorilla]-[version of PHP]-[ts or nts]-[architecture].zip

DLL features (PHP version, TS or NTS and architecture) must be matched php.exe's.  
TS means Thread Safe, and NTS means Non Thread Safe. Architecture may be x86 or x64.  
For example, Gorilla-0.5.0-5.5-ts-x86.zip includes DLL for php.exe which is,

 * version 5.5.x
 * thread safe 
 * 32bit(x86)


### Install DLL

Follow next step to enable Gorilla.

 1. save php_Gorilla.dll into your ```extension_dir```.
 2. add ```extension=php_Gorilla.dll``` to your php.ini

Please confirm ```extension_dir``` directive in php.ini.

Run next command, to make sure that installation has succeeded.

    php -i

Or run phpinfo() script,

    <?php
    phpinfo();

You can see information about this extension.


BASIC USAGE
===========

```php
    <?php
    use PHPMake\SerialPort;
    // $device = 'COM4'; // on Windows
    $device = '/dev/ttyUSB0'; // on Linux 

    /*
     * create new instance
     */
    $port = new SerialPort();

    try {
        /* 
         * open the port
         */
        $port->open($device);
    
        /*
         * configure baud rate
         *
         * you can specify baud rate as integer, 
         * or other class constants like SerialPort::BAUD_RATE_*
         */
        $port->setBaudRate(SerialPort::BAUD_RATE_9600);
    
        /*
         * configure flow control
         * 
         * any other options are below.
         * SerialPort::FLOW_CONTROL_SOFT is software flow control.
         * SerialPort::FLOW_CONTROL_HARD is hardware flow control.
         */
        $port->setFlowControl(SerialPort::FLOW_CONTROL_NONE);
    
        /*
         * configure canonical mode
         * 
         * canonical mode is for text-based communication.
         * non-canonical mode is binary-safe.
         * more detail information about VMIN and VTIME, 
         * see http://www.unixwiz.net/techtips/termios-vmin-vtime.html
         */
        $port->setCanonical(false)
                ->setVTime(1)->setVMin(0);
    
        /*
         * read data from port.
         * you can get size of actual read data with strlen($data) .
         */
        $data = $port->read(256);
    
        /*
         * send data.
         */
        $port->write($data);
    
    } catch (Exception $e) {
        print $e->getMessage() . PHP_EOL;
    }

    if ($port->isOpen()) $port->close();

```


TESTING
=======

You can now load the extension using a php.ini directive

    extension="Gorilla.[so|dll]"

or load it at runtime using the dl() function

    dl("Gorilla.[so|dll]");

The extension should now be available, you can test this
using the extension_loaded() function:

    if (extension_loaded("Gorilla"))
      echo "Gorilla loaded :)";
    else
      echo "something is wrong :(";

The extension will also add its own block to the output
of phpinfo();




HACKING
=======

There are two ways to modify an extension created using CodeGen_PECL:

1) you can modify the generated code as with any other PHP extension
  
2) you can add custom code to the CodeGen_PECL XML source and re-run pecl-gen

The 2nd approach may look a bit complicated but you have be aware that any
manual changes to the generated code will be lost if you ever change the
XML specs and re-run PECL-Gen. All changes done before have to be applied
to the newly generated code again.
Adding code snippets to the XML source itself on the other hand may be a 
bit more complicated but this way your custom code will always be in the
generated code no matter how often you rerun CodeGen_PECL.

