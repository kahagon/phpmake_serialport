<?php

use PHPMake\SerialPort as SerialPort;

/* シリアルポートを開きます */
$port = new SerialPort('COM3');

/* ボーレートを 9600 に設定します */
$port->setBaudRate(SerialPort::BAUD_RATE_9600);

/* フロー制御は行いません */
$port->setFlowControl(SerialPort::FLOW_CONTROL_NONE);

/* 
 * データの読み込みにカノニカル入力モードを用いません。
 * この設定では SerialPort::read() は
 * 最低1バイト読み込むまで呼び出し元に制御を戻しません。
 */
$port->setCanonical(false)
        ->setVTime(0)->setVMin(1);

/* データを送信します。 */
$written = $port->write('hello');

/* 
 * 最大256バイトまでデータを読み込みます。
 * 上で行った読み込みタイムアウトの設定と合わせると、
 * SerialPort::read() は次のように振る舞います。
 * 
 * - 最低1バイト読み込むまでブロックする
 * - 最大256バイト読み込む
 * 
 * 実際に読み込まれたデータのサイズは 
 * strlen($data) 
 * などとして求められます。
 */
$data = $port->read(256);
$dataSize = strlen($data);
var_dump($data);

/* ポートを閉じます */
$port->close();
