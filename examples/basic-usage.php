<?php
if ($argc != 2) {
    print 
        'Usage: php ' . basename(__FILE__) . ' port_string' . PHP_EOL .
        '    port_string     接続するポート' . PHP_EOL;
    exit (1);
}

$status = 0;
$portString = $argv[1];

/**
 * SerialPort のインスタンスを作ります。
 * SerialPort::__construct(string $portString) でインスタンスを生成する場合は、
 * 以下に続く SerialPort::open(string $portString) もコンストラクタ内で行われます。
 */
$port = new SerialPort();


try {
    /* 
     * $portString が示すシリアルポートとのストリームを開きます。
     * コンストラクタ SerialPort::__construct(string $portString) でインスタンスを生成している場合は、
     * SerialPort::open(string $portString) をコールする必要はありません。
     */
    $port->open($portString);
    
    /*
     *  ボーレートを設定します。
     * ここではクラス定数を用いていますが整数リテラルでも構いません。
     */
    $port->setBaudRate(SerialPort::BAUD_RATE_9600);
    
    /*
     * フロー制御を設定します。
     * SerialPort::setFlowControl() の引数には
     * クラス定数 SerialPort::FLOW_CONTROL_* を用いてください。
     */
    $port->setFlowControl(SerialPort::FLOW_CONTROL_NONE);
    
    /*
     * カノニカルモードを設定します。
     * 続く SerialPort::setVMin() SerialPort::setVTime() と共に
     * データ読み込み時のタイムアウト方法を決定します。
     * 
     * この設定では読み込み可能なデータがあればそれを読み込み返します。
     * 読み込み可能なデータがない場合に 0.1 秒データを待ちます（0.1秒ブロックします）。
     */
    $port->setCanonical(false)
            ->setVTime(1)->setVMin(0);
    
    /*
     * データを 256 バイト読み込みます。引数を省略した場合1バイト読み込みます。
     * このメソッドは必ずしも指定したバイト数を読み込むとは限りません。
     * 実際に読み込んだバイト数は strlen($data) で確認できます。
     */
    $data = $port->read(256);
    
    /*
     * $data を送信します。
     * 読み込んだデータをそのまま返すこの挙動は echo server に似ています。
     */
    $port->write($data);
    
} catch (Exception $e) {
    print $e->getMessage() . PHP_EOL;
    $status = 2;
}

/*
 * SerialPort::isOpen() はシリアルポートが開かれているかどうか調べます。
 */
if ($port->isOpen()) {
    /*
     * SerialPort::close() でシリアルポートとのストリームを閉じます。
     */
    $port->close();
}

exit ($status);