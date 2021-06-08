因為有三大題，所以這次readme我分為三大題來講，每一小題分別講how to setup和result<br>
## hw4_1 XBee Controlled BB Car
(1) how to setup and run my program <br>
1. 一開始先將車車組裝起來(就是像課程網站的那樣步驟，在下面的連結)<br>
<https://www.ee.nthu.edu.tw/ee240500/mbed-lab-13-boe-bot-car.html>
(注意) 要記得這裡的馬達左輪的訊號線是接到D5，而右輪是接到D6<br>
2. 接下來將xbee給裝在車子上面的白色小板板，然後依照下面的指示來接pin角<br>
xbee的5V接到板子的5V<br>
xbee的GND接到板子的GND<br>
xbee的rx接到板子的D0<br>
xbee的tx接到板子的D1<br>

3. 再來要組建好場地(如下圖)
![image](https://github.com/NormalChen0122/hw4/blob/master/pictures/map_of_hw4_1.jpg)<br>
(注意) 要記得這裡停車格的的寬度不能超過車車的寬度4公分<br>

4. 接下來就可以將B_L4S5I_IOT01A和notebook給接起來<br>
5. 然後輸入此command，將code給燒入B_L4S5I_IOT01A(要注意command裡面的那個ee2405v3那個要看自己的mbed-os-build是在哪個資料夾底下，來去做改變)<br>
```sudo mbed compile --source . --source ~/ee2405v3/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM --profile tflite.json -f```
6. 待燒入完成後，就把原本接在電腦上的，改接到行動電源上，按下B_L4S5I_IOT01A的reset button(也就是在藍色按鈕旁邊的黑色按鈕)<br>
7. 再來將另一個xbee給連到電腦上
(注意) 在這之前兩個xbee的ATMY和ATDL都要先設定好可以互相溝通了喔<br>
8. 接下來把車子放在要開始的起始點，並且用頭腦記住d1, d2和direction
![image](https://github.com/NormalChen0122/hw4/blob/master/pictures/map_of_hw4_1.jpg)<br>

9. 接下來在host的terminal上輸入下列command<br>
```sudo python3 parking.py```

10. 他會依序要我們填入d1, d2, direction，只要照指示填入就好了，之後按下enter，車子就會開始跑了

(2) what are the results<br>
因為是會動的，所以看影片會比較快，影片所在的連結如下<br>
<https://drive.google.com/drive/folders/1WVonpZWLLrN1j5j2MCpW-5EuorRf-ZYQ?usp=sharing>

## hw4_2 Line Following BB Car
(1) how to setup and run my program <br>
1. 一開始先依照lab14的課程網站上面一樣，將openMV的板子裝在車車上(連結如下)<br>
<https://www.ee.nthu.edu.tw/ee240500/mbed-lab-14-machine-vision-with-openmv-h7-plus.html>
2. 接下來將依照下面的指示來接pin角<br>
openMV的p5接到D1<br>
openMV的p4接到D0<br>
openMV的reset接到mbed的reset<br>
4. 接下來就可以將B_L4S5I_IOT01A和notebook給接起來<br>
5. 然後輸入此command，將code給燒入B_L4S5I_IOT01A(要注意command裡面的那個ee2405v3那個要看自己的mbed-os-build是在哪個資料夾底下，來去做改變)<br>
```sudo mbed compile --source . --source ~/ee2405v3/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM --profile tflite.json -f```
6. 接下來把openMV和notebook連接，將main.py給改成我github放在hw4_2/For_openMV裡面的hw4_2.py
7. 接下來就可以把USB插頭給接到行動電源上，並且因為老師發的金色的線有兩個頭，所以可以分別插在openMV和mbed上(如下圖)<br>
![image](https://github.com/NormalChen0122/hw4/blob/master/pictures/hw4_2_connect.jpg)<br>
8. 然後建構好地圖(如下圖)<br>
![image](https://github.com/NormalChen0122/hw4/blob/master/pictures/map_of_hw4_2.jpg)<br>
9. 接下來就把車子按reset然後放在黑線的尾端，他就會沿著線跑了<br>

(2) what are the results<br>
因為是會動的，所以看影片會比較快，影片所在的連結如下<br>
<https://drive.google.com/drive/folders/1WVonpZWLLrN1j5j2MCpW-5EuorRf-ZYQ?usp=sharing>

## hw4_3 BB Car Position Calibration
(1) how to setup and run my program <br>
1. 一開始先將uLCD display和B_L4S5I_IOT01A相接，角位如下<br>
serial rx接到D9<br>
serial tx接到D10<br>
reset pin接到D2<br>
5V接到5V<br>
GND接到GND<br>
(注意) 要記得這裡的rx, tx, reset不是看uLCD板子上的，而是線上面的<br>

2. 接下來將ping插在車子上的小板板上，然後依照課程網站上面的方式連接(連結如下)<br>
<https://www.ee.nthu.edu.tw/ee240500/mbed-lab-12-servos-encoder-and-ping.html>
(注意) 要記得這裡的sig我是設定接到D12<br>
3. 接下來就可以將B_L4S5I_IOT01A和notebook給接起來<br>
![image](https://github.com/NormalChen0122/hw3_new/blob/master/hw3_picture/mbed_pc.jpg)<br>
4. 然後輸入此command，將code給燒入B_L4S5I_IOT01A(要注意command裡面的那個ee2405v3那個要看自己的mbed-os-build是在哪個資料夾底下，來去做改變)<br>
```sudo mbed compile --source . --source ~/ee2405v3/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM --profile tflite.json -f```
5. 接下來把openMV和notebook連接，將main.py給改成我放在hw4_3/For_openMV裡面的hw4_3.py
6. 接下來就可以把USB插頭給接到行動電源上，並且因為老師發的金色的線有兩個頭，所以可以分別插在openMV和mbed上(如下圖)<br>
![image](https://github.com/NormalChen0122/hw4/blob/master/pictures/hw4_2_connect.jpg)<br>
7. 然後建構好地圖(如下圖)<br>
![image](https://github.com/NormalChen0122/hw4/blob/master/pictures/map_of_hw4_3.jpg)<br>

8. 待上面都完成後，按下B_L4S5I_IOT01A的reset button(也就是在藍色按鈕旁邊的黑色按鈕)，將車子放在地圖上，並且使得鏡頭裡面有AprilTag就好<br>
9. 最後他就會開始自己對準，然後開始走，一直到完全正面對AprilTag(此時如果拿到其他地方，車車還是可以繼續往AprilTag走，然後重新正對AprilTag)


(2) what are the results<br>
因為是會動的，所以看影片會比較快，影片所在的連結如下<br>
<https://drive.google.com/drive/folders/1WVonpZWLLrN1j5j2MCpW-5EuorRf-ZYQ?usp=sharing>
