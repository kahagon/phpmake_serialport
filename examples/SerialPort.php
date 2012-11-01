<?php
/**
 * この PHP ファイルは PHP 拡張 Gorilla の SerialPort クラスのインタフェースと簡単な説明を示したものです。
 * 本来 PHP 拡張のドキュメンテーションは docbook 形式で書き PhD というツールを用いるべきですが、
 * author の紅茶花伝が切れたので phpDocumentor に頼ることになりあｓふぁふぁ
 * 
 * @author Keng-ichi Ahagon <k.ahagon@n-3.so>
 */

/**
 * シリアルポートを表現するクラスです。
 * 対象のデバイス・端末に接続し、データの送受信を行います。
 */
class SerialPort {
    
  /**
   * このシリアルポートが接続しているデバイスを示す文字列。
   * このプロパティは SerialPort::open() あるいはコンストラクタに渡されるデバイスを指定する文字列と同一です。
   * 
   * @var string
   */
  protected $_device;
  
  /**
   * このシリアルポートが接続しているデバイスとのストリーム
   * @var resource
   */
  protected $_stream;
  
  /**
   * SerialPort::$_stream の file descriptor
   * @var int 
   */
  private $_streamFd;

  /**
   * SerialPort の新しいインスタンスを生成します。
   * 引数 $device が与えられた場合、そのデバイスに接続します。
   * $device を指定しない場合はデバイスに対する操作の前に SerialPort::open() をコールしなければなりません。
   * 
   * @param string $device デバイスファイル名
   * @see SerialPort::open()
   */
  public function __construct($device = "") {}
  
  /**
   * デバイスをオープンし接続します。
   * コンストラクタでデバイスを指定した場合はこのメソッドをコールする必要はありません。
   * 
   * @param string $device デバイスファイル名
   * @return self このインスタンス
   * @see SerialPort::__construct()
   */
  public function open($device) {}
  
  /**
   * デバイスをクローズします。
   * 
   * @return bool 成功した場合に true 、失敗した場合に false
   */
  public function close() {}
  
  /**
   * デバイスをオープンしているかどうか調べます。
   * 
   * @return bool デバイスをオープンしている場合に true を、そうでない場合に false
   */
  public function isOpen() {}
  
  /**
   * デバイスから $length バイト分のデータを読み込み返します。
   * 
   * @param int $length
   * @return string デバイスから読み込んだデータ
   * @throws Exception 引数 $length に負数が与えられたときにスローされます。
   */
  public function read($length = 0) {}
  
  /**
   * 与えられたデータを対象のデバイスに送信します。
   * 
   * @param string $data 送信するデータ
   * @return int 実際に送信されたデータのバイト数
   */
  public function write($data) {}
  
  /**
   * 対象のデバイスの CTS(Clear to Send 送信許可)を取得します。
   * 
   * @return bool CTS フラグ
   */
  public function getCTS() {}
  
  /**
   * このシリアルポートの RTS(Request to Send 送信要求)を取得します。
   * 
   * @return bool RTS フラグ
   */
  public function getRTS() {}
  
  /**
   * このシリアルポートの RTS をセットします。
   * 
   * @param bool $rts
   * @return self このインスタンス
   */
  public function setRTS($rts) {}
  
  /**
   * 対象のデバイスの DSR(Data Set Ready データセットレディ)を取得します。
   * 
   * @return bool DSR フラグ
   */
  public function getDSR() {}
  
  /**
   * このシリアルポートの DTR(Data Terminal Ready データ端末レディ)を取得します。
   * 
   * @return bool DTR フラグ
   */
  public function getDTR() {}
  
  /**
   * このシリアルポートの DTR をセットします。
   * 
   * @param bool $dtr
   * @return self このインスタンス
   */
  public function setDTR($dtr) {}
  
  /**
   * DTD(Date Carrier Detect キャリア検出)を取得します。
   * 
   * @return bool DCD フラグ
   */
  public function getDCD() {}
  
  /**
   * RNG(Ring Indicator 被呼表示)を取得します。
   * 
   * @return bool RNG(または RI) フラグ
   */
  public function getRNG() {}
 
  /**
   * このシリアルポートの現在のボーレートを取得します。
   * 
   * @return int 現在のボーレート値
   */
  public function getBaudRate(){}
  
  /**
   * このシリアルポートのボーレートを $baudRate に設定します。
   * $baudRate に指定可能な値はクラス定数 SerialPort::BAUD_RATE_* を参照してください。
   * 
   * @param int $baudRate ボーレート
   * @return self このインスタンス
   * @throws Exception SerialPort::BAUD_RATE_* に無い値を指定した場合
   */
  public function setBaudRate($baudRate){}
  
  /**
   * 現在設定されているデータビット数を取得します。
   * クラス定数 SerialPort::CHAR_SIZE_* も参照してください。
   * 
   * @return int 現在のデータビット数
   */
  public function getCharSize() {}
  
  /**
   * データビット数を設定します。
   * 引数 $charSize にはクラス定数 SerialPort::CHAR_SIZE_* で定義されている値を指定してください。
   * それ以外の値が渡された場合に Exception がスローされます。
   * 
   * @param int $charSize データビット数
   * @return self このインスタンス
   * @throws Exception 引数に、クラス定数 SerialPort::CHAR_SIZE_* で定義されていない値が指定された場合
   */
  public function setCharSize($charSize) {}
  
  /**
   * 現在のフロー制御を表す文字列を返します。
   * クラス定数 SerialPort::FLOW_CONTROL_* も参照してください。
   * 
   * @return string フロー制御を表す文字列
   */
  public function getFlowControl() {}
  
  /**
   * フロー制御を変更します。
   * 引数 $flowControl にはクラス定数 SerialPort::FLOW_CONTROL_* で定義されている文字列を指定してください。
   * それ以外の文字列が指定された場合に Exception がスローされます。
   * 
   * @param string $flowControl フロー制御を表す文字列
   * @return self このインスタンス
   * @throws Exception 引数にクラス定数 SerialPort::FLOW_CONTROL_* で定義されていない文字列が指定された場合
   */
  public function setFlowControl($flowControl) {}
  
  /**
   * 現在のストップビットのビット数を返します。
   *  1 もしくは 2 が値として返ります。
   * 
   * @return int ストップビットのビット数
   */
  public function getNumOfStopBits() {}
  
  /**
   * ストップビットのビット数を変更します。
   * 引数 $numOfStopBits に指定可能な値は 1 もしくは 2 です。
   * それ以外の値が指定された場合に Exception がスローされます。
   * 
   * @param int $numOfStopBits ストップビットのビット数
   * @return self このインスタンス
   * @throws Exception 引数に 1 もしくは 2 以外の値が指定された場合
   */
  public function setNumOfStopBits($numOfStopBits) {}

  /**
   * 現在のパリティチェックの方法を取得します。
   * クラス定数 SerialPort::PARITY_* も参照してください。
   * 
   * @return string パリティチェック方法を示す文字列
   */
  public function getParity() {}
  
  /**
   * パリティチェックの方法を変更します。
   * 引数 $parity にはクラス定数 SerialPort::PARITY_* で定義されている文字列を指定してください。
   * それ以外の値が指定された場合に Exception がスローされます。
   * 
   * @param string $parity パリティチェック方法を示す文字列
   * @return self このインスタンス
   * @throws Exception クラス定数 SerialPort::PARITY_* で定義されていない文字列が指定された場合
   */
  public function setParity($parity) {}
  
  /**
   * カノニカルモード・非カノニカルモードを切り替えます。
   * 引数 $canonical に true が指定された場合、カノニカルモードに切り替わります。
   *  false が指定された場合、非カノニカルモードに切り替わります。
   * 
   * @param bool $canonical
   * @return self このインスタンス
   */
  public function setCanonical($canonical) {}
  
  /**
   * カノニカルモードかどうかを判定します。
   * カノニカルモードの場合に true 、非カノニカルモードの場合に false を返します。
   * 
   * @return bool カノニカルモードの場合に true 、非カノニカルモードの場合に false
   * @see SerialPort::setVMin()
   * @see SerialPort::setVTime()
   */
  public function isCanonical() {}
  
  /**
   * 現在設定されている VMIN の値を返します。
   * 
   * @return int 現在の VMIN 値
   * @see SerialPort::setVMin()
   */
  public function getVMin() {}
  
  /**
   * VMIN は SerialPort::read() 時のタイムアウトを規定します。
   * タイムアウトの振る舞いは VMIN VTIME の値、カノニカルモードであるかどうかにより規定されます。
   * 
   * @param int $vmin
   * @return self このインスタンス
   * @see SerialPort::setCanonical()
   * @see SerialPort::setVTime()
   */
  public function setVMin($vmin) {}
  
  /**
   * 現在設定されている VTIME の値を返します。
   * 
   * @return int 現在の VTIME 値
   * @see SerialPort::setVTime()
   */
  public function getVTime() {}
  
  /**
   * VTIME は SerialPort::read() 時のタイムアウトを規定します。
   * タイムアウトの振る舞いは VMIN VTIME の値、カノニカルモードであるかどうかにより規定されます。
   * 
   * @param int $vtime
   * @return self このインスタンス
   * @see SerialPort::setCanonical()
   * @see SerialPort::setVMin()
   */
  public function setVTime($vtime) {}


  /**
   * EVEN パリティチェック
   */
  const PARITY_EVEN = "PARITY_EVEN";
  
  /**
   * ODD パリティチェック
   */
  const PARITY_ODD = "PARITY_ODD";
  
  /**
   * パリティチェックなし
   */
  const PARITY_NONE = "PARITY_NONE";
  
  /**
   * デフォルトのパリティチェック。実際は SerialPort::PARITY_NONE 。
   */
  const PARITY_DEFAULT = SerialPort::PARITY_NONE;

  /**
   * ハードウェア・フロー制御
   */
  const FLOW_CONTROL_HARD = "FLOW_CONTROL_HARD";
  
  /**
   * ソフトウェア・フロー制御
   */
  const FLOW_CONTROL_SOFT = "FLOW_CONTROL_SOFT";
  
  /**
   * フロー制御なし
   */
  const FLOW_CONTROL_NONE = "FLOW_CONTROL_NONE";
  
  /**
   * デフォルトのフロー制御。実際は SerialPort::FLOW_CONTROL_NONE 。
   */
  const FLOW_CONTROL_DEFAULT = SerialPort::FLOW_CONTROL_NONE;

  const CHAR_SIZE_5 = 5;
  const CHAR_SIZE_6 = 6;
  const CHAR_SIZE_7 = 7;
  const CHAR_SIZE_8 = 8;
  const CHAR_SIZE_DEFAULT = SerialPort::CHAR_SIZE_8;

  const BAUD_RATE_50 = 50;
  const BAUD_RATE_75 = 75;
  const BAUD_RATE_110 = 110;
  const BAUD_RATE_134 = 134;
  const BAUD_RATE_150 = 150;
  const BAUD_RATE_200 = 200;
  const BAUD_RATE_300 = 300;
  const BAUD_RATE_600 = 600;
  const BAUD_RATE_1200 = 1200;
  const BAUD_RATE_1800 = 1800;
  const BAUD_RATE_2400 = 2400;
  const BAUD_RATE_4800 = 4800;
  const BAUD_RATE_9600 = 9600;
  const BAUD_RATE_19200 = 19200;
  const BAUD_RATE_38400 = 38400;
  const BAUD_RATE_57600 = 57600;
  const BAUD_RATE_115200 = 115200;
  const BAUD_RATE_230400 = 230400;
}
