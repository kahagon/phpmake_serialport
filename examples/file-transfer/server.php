<?php
if ($argc != 3) {
  $filename = basename(__FILE__);
  $usage =<<<EOU
port から送信されてきたファイルを dir に保存します。
使い方: php $filename port dir
    port    対象のシリアルポート
    dir     受信したファイルの保存ディレクトリ

EOU;
  print $usage;
  exit(1);
}

require_once 'file-transfer-classes.php';
new Server($argv[1], $argv[2]);
