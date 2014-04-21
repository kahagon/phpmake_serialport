<?php
use PHPMake\SerialPort as SerialPort;

$status = 0;
$deviceName = $_POST['device'];

if ($deviceName) {
  /**
   * SerialPort のインスタンスを作ります。
   * SerialPort::__construct(string $portString) でインスタンスを生成する場合は、
   * 以下に続く SerialPort::open(string $portString) もコンストラクタ内で行われます。
   */
  $port = new SerialPort();

  try {
      /* 
       * $portString が示すシリアルポートとのストリームを開きます。
       * コンストラクタ SerialPort::__construct(string $deviceName) でインスタンスを生成している場合は、
       * SerialPort::open(string $deviceName) をコールする必要はありません。
       */
      $port->open($deviceName);
      
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
       * リクエストパラメータ data を端末に送信します。
       * この例では単純に変数に代入して端末に送信しますが、
       * 本来は実際のアプリケーションに即したバリデーションや
       * フィルタリングなどを行うべきです。
       */
      $data = $_POST['data'];
      
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
}
?>
<html>
  <head>
    <title>Testing \PHPMake\SerialPort</title>
  </head>
  <body>
    <form action="<?php print basename(__FILE__); ?>" method="POST">
      <label for="deviceName">deviceName</label>: <input type="text" name="deviceName" id="deviceName" /><br />
      <label for="data">data</label><br />
      <textarea name="data" id="data"></textarea><br />
      <input type="submit" value="submit" />
    </form>
  </body>
</html>
