インストール
=============

php_Gorilla.dll を `extension_dir` にコピーしてください。  
`extension_dir` は php.ini によって指定されています。 php.ini を確認してください。

php.ini に以下の記述を追加します。

    extension=php_Gorilla.dll

以上でインストールは完了です。


コマンドラインから

    php -i

あるいは php スクリプト

    <?php
    phpinfo();

で Gorilla のインストールを確認できるはずです。
