# bbb_info_app

這是一個可以查看bigbluebutton會議狀況的程式，像是會議名稱，開啟日期或是參加會議的人，也可以得到以管理者身份加入會議的網址

## 使用方法

1. 先編譯並製作執行檔

   ```shell
   cd bbb_info_app
   mkdir build
   ccmake ..
   make
   ```

2. __製作一個  `<檔案名稱>.secret`   的檔案，檔案內容為要查詢的那台伺服器的shared secret，製作完之後就可以使用本程式。__

3. 接者輸入要查詢server的domain name，像是bbb.ical.tw。

4. 然後選擇剛剛製作的`.secret`的檔案，就可以按`get Info`按鈕即可得到會議資訊。
5. 得到會議資訊後可以按`Meeting`裡的按鈕進一步得到會議的開啟日期與參加會議的人，更可以得到以管理者身份加入會議的網址(按下`copy`按鈕即可複製網址)。
