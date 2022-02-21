![image](https://user-images.githubusercontent.com/67863963/154849136-5426114f-a9ab-4668-9066-afd72c11b04c.png)

M5Stackで遊ぶRoll a Ballゲームです。
M5Core2でのみ動作確認しています。
MPU6886搭載の他機種でも(ソースをいじれば)動作すると思います。


Create IMU6886_offset_corr_BT.ino

…M5Core2に書き込むプログラムです。
 まず、M5を水平な面においてAボタンを1秒ほど押し、キャリブレーションしてください。
 「Calibration！」と表示され、pitchとrollが0付近になれば成功です。
 再度キャリブレーションする際は一度リセットが必要です。
 

Roll_a_Ball.exe

…Unityで作成したゲーム本体です。

![image](https://user-images.githubusercontent.com/67863963/154849363-50c207f2-5f2b-4872-a129-8b61b0f128b4.png)

起動後、上図の入力窓にシリアルポートNoを入力し、Enterでゲームスタートです。
Bluetoohシリアルが使えます。

あまり速く動かすと、ボールがステージにめり込んで消えてしまいます…
ボールが消えたらキーボードの"r"を押してリスタートしてください（また初めから）


## Reference
https://fabterrace.site/2021/04/13/unity%E3%81%A8arduino%E3%81%A7%E7%B0%A1%E5%8D%98%E3%81%AA%E3%82%B2%E3%83%BC%E3%83%A0%E3%82%92%E4%BD%9C%E6%88%90%E3%81%97%E3%81%A6%E3%81%BF%E3%81%9F%E3%80%82/

https://github.com/m5stack/M5Core2/tree/master/examples/Basics/mpu6886
