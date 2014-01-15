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
TS means Thread Safe, and NTS means Non Thread Safe.  
Architecture may be x86 or x64.

For example, Gorilla-0.5.0-5.5-ts-x86.zip includes DLL for thread safe PHP-5.5 which is 32bit.


### Install DLL

Follow next step to enable Gorilla.

 1. save php_Gorilla.dll into your ```extension_dir```.
 2. add ```extension=php_Gorilla.dll``` to your php.ini

Please confirm extension_dir directive in php.ini.

Run next command, to make sure that installation has succeeded.

    php -i

Or run phpinfo() script,

    <?php
    phpinfo();

You can see information about this extension.


BUILDING ON WINDOWS
===================

The extension provides the VisualStudio V6 project file 

  Gorilla.dsp
To compile the extension you open this file using VisualStudio,
select the apropriate configuration for your installation
(either "Release_TS" or "Debug_TS") and create "php_Gorilla.dll"

After successfull compilation you have to copy the newly
created "Gorilla.dll" to the PHP
extension directory (default: C:\PHP\extensions).



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

