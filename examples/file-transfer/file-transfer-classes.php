<?php

class Server {

  private $_port;
  private $_baseDir = './';
  private $_status;
  private $_chunkSize = 1024;

  private $_limit = 30;
  private $_statusChanged;

  private $_fileName = '';
  private $_fileSize = 0;
  private $_currentFileSize = 0;
  private $_fileHandle = null;
  private $_fileDataBuf = '';

  public function __construct($portName, $baseDir) {
    if (!chdir($baseDir)) {
      throw new Exception('そのようなディレクトリはありません。');
    }
    $this->_port = new SerialPort($portName);
    $this->_port
      ->setBaudRate(9600)
      ->setFlowControl(SerialPort::FLOW_CONTROL_NONE)
      ->setCanonical(false)
      ->setVMin(0)->setVTime(1);
    $this->_status = self::WAIT_FOR_START;
    $this->_run();
  }

  function _changeStatus($status) {
    $this->_status = $status;
    $this->_statusChanged = time();
  }

  function _resetStatus() {
    print 'リセットします。' . PHP_EOL;
    $this->_status = self::WAIT_FOR_START;
    $this->_fileName = '';
    $this->_fileDataBuf = '';
    $this->_fileSize = 0;
    $this->_currentFileSize = 0;
    if ($this->_fileHandle) {
      fclose($this->_fileHandle);
      $this->_fileHandle = null;
    }
    while ($this->_port->read($this->_chunkSize)) ;
  }

  function _processStart($data) {
    if ($data == Client::REQUEST_START) {
      $this->_changeStatus(self::WAIT_FOR_SPEC_FILE_NAME);
      $this->_port->write(self::RESPONSE_START_OK);
    } else if (strlen($data) == 0) {
      // nothing
    } else {
      $this->_resetStatus();
      $this->_port->write(self::RESPONSE_FAILED);
    }
  }

  function _processSpecFileName($data) {
    print 'ファイル名: ' . $data . PHP_EOL;
    $fh = fopen($data, 'w');
    if ($fh) {
      $this->_fileHandle = $fh;
      $this->_changeStatus(self::WAIT_FOR_SPEC_FILE_SIZE);
      $this->_port->write(self::RESPONSE_SPEC_FILE_NAME_OK);
    } else {
      $this->_resetStatus();
      $this->_port->write(self::RESPONSE_SPEC_FILE_NAME_FAILED);
    }
  }

  function _processSpecFileSize($data) {
    if (is_numeric($data)) {
      $this->_fileSize = intval($data);
      $this->_changeStatus(self::WAIT_FOR_DATA);
      $this->_port->write(self::RESPONSE_SPEC_FILE_SIZE_OK);
    } else {
      $this->_resetStatus();
      $this->_port->write(self::RESPONSE_SPEC_FILE_SIZE_FAILED);
    }
  }

  function _processData($data) {
    $this->_fileDataBuf .= $data;
    $this->_currentFileSize = strlen($this->_fileDataBuf);
    if ($this->_currentFileSize == $this->_fileSize) {
      $this->_port->write(self::RESPONSE_END_OK);
      $result = fwrite($this->_fileHandle, $this->_fileDataBuf);
      if ($result) {
        print 'ファイルを保存しました。' . PHP_EOL;
      } else {
        print '保存に失敗しました。' . PHP_EOL;
      }
      $this->_resetStatus();
    } else if ($this->_currentFileSize < $this->_fileSize) {
      //nothing
    } else {
      $this->_resetStatus();
      unlink($this->_fileName);
      $this->_port->write(self::RESPONSE_END_FAILED_FILE_SIZE);
    }
  }

  function _run() {
    print '起動しました。' . PHP_EOL;
    while (true) {
      $data = $this->_port->read($this->_chunkSize);
      if ($data == Client::REQUEST_RESET) {
        $this->_resetStatus();
        continue;
      }


      if (strlen($data)) {
       switch ($this->_status) {
         case self::WAIT_FOR_SPEC_FILE_NAME:
           $this->_processSpecFileName($data);
           break;
         case self::WAIT_FOR_SPEC_FILE_SIZE:
           $this->_processSpecFileSize($data);
           break;
         case self::WAIT_FOR_DATA:
           $this->_processData($data);
           break;
         default:
         case self::WAIT_FOR_START:
           $this->_processStart($data);
           break;
        }
      }

      if (
        $this->_status != self::WAIT_FOR_START 
        && (time() - $this->_statusChanged >= $this->_limit)) 
      {
        print '相手はどっかに行ってしまったようです。。' . PHP_EOL;
        $this->_resetStatus();
      }
    }
  }

  const WAIT_FOR_START = 1;
  const WAIT_FOR_SPEC_FILE_NAME = 2;
  const WAIT_FOR_SPEC_FILE_SIZE = 3;
  const WAIT_FOR_DATA = 4;

  const RESPONSE_FAILED = 'ちょっと言っている意味がわかりません。';
  const RESPONSE_START_OK = 'いいですよ。ファイル名を教えてください。';
  const RESPONSE_START_FAILED = '少しお待ちください。';
  const RESPONSE_SPEC_FILE_NAME_OK = 'ファイル名OKです。次はファイルサイズを教えてください。';
  const RESPONSE_SPEC_FILE_NAME_FAILED = 'そのファイル名はだめです。';
  const RESPONSE_SPEC_FILE_SIZE_OK = 'ファイルサイズOKです。教えていただいたファイルサイズに達するまでデータを送信してください。';
  const RESPONSE_SPEC_FILE_SIZE_FAILED = 'ファイルサイズダメです。';
  const RESPONSE_END_OK = 'ファイルはちゃんと受け取りました。';
  const RESPONSE_END_FAILED_FILE_SIZE = 'ファイルサイズが言ってたサイズより大きいですよ？';
  const RESPONSE_END_FAILED = 'ファイル受け取りに失敗しました。';
}

class Client {

  private $_port;
  private $_chunkSize = 1024;

  public function __construct($portName) {
    $this->_port = new SerialPort($portName);
    $this->_port
      ->setBaudRate(9600)
      ->setFlowControl(SerialPort::FLOW_CONTROL_NONE)
      ->setCanonical(false)
      ->setVMin(0)
      // Server の VTIME 値よりも大きくないといけない。
      // Server::_sendData() で最後のチャンクを Server が受け取る際の
      // read タイムアウトよりも先にタイムアウトさせないため。
      ->setVTime(3);
  }

  function _expect($expect) {
    $res = $this->_port->read($this->_chunkSize);
    return $res == $expect;
  }

  function _talk($data, $expect) {
    $this->_port->write($data);
    $res = $this->_expect($expect);
    if (!$res) {
      $this->_port->write(self::REQUEST_RESET);
    }
    return $res;
  }

  function _sendData($filePath) {
    $fh = fopen($filePath, 'rb');
    if (!$fh) {
      print '指定されたファイルを開けませんでした。' . PHP_EOL;
      return;
    }

    while (!feof($fh)) {
      $fragment = fread($fh, $this->_chunkSize);
      $this->_port->write($fragment);
      unset($fragment);
    }
    fclose($fh);

    $res = $this->_expect(Server::RESPONSE_END_OK);
    if ($res) {
      print 'ファイル送信しました！' . PHP_EOL;
    } else {
      print 'ファイル送信に失敗しました。。' . PHP_EOL;
    }

  }

  public function sendFile($filePath) {
    $filePath = realPath($filePath);
    if (!$filePath) {
      print '指定されたファイルは存在しません。' . PHP_EOL;
      return;
    }

    while ($this->_port->read($this->_chunkSize)) ;

    $res = $this->_talk(self::REQUEST_START, Server::RESPONSE_START_OK);
    if (!$res) {
      print '今、ファイル送れないみたいです。' . PHP_EOL;
      return;
    }

    $res = $this->_talk(basename($filePath), Server::RESPONSE_SPEC_FILE_NAME_OK);
    if (!$res) {
      print 'ファイル名がダメだそうです。' . PHP_EOL;
      return;
    }

    $res = $this->_talk(filesize($filePath), Server::RESPONSE_SPEC_FILE_SIZE_OK);
    if (!$res) {
      print 'ファイルサイズがダメだそうです。' . PHP_EOL;
      return;
    }

    $this->_sendData($filePath);
  }

  const REQUEST_START = 'ファイル送りたいんですけどいいですか？';
  const REQUEST_RESET = 'リセットお願いします。';
}



























