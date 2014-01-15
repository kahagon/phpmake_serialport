INSTALL
==========

Copy php_Gorilla.dll into `extension_dir`.
Please confirm extension_dir directive in php.ini.

To enable this extension, add next line to php.ini

    extension=php_Gorilla.dll

Run next command, to make sure that installation has succeeded.

    php -i

Or run phpinfo() script,

    <?php
    phpinfo();

You can see information about this extension.
