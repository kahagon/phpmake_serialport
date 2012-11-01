<?php
if ($argc != 3) {
  $filename = basename(__FILE__);
  $usage =<<<EOU
対象のポートにファイルを送信します。
使い方: php $filename port file
    port    対象のシリアルポート
    file    送信するファイル

EOU;
  print $usage;
  exit(1);
}

require_once 'file-transfer-classes.php';
$c = new Client($argv[1]);
$c->sendFile($argv[2]);
