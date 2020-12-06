#include "pgmspace.h"

char indexHtml[] PROGMEM = R"=====(
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-alpha3/dist/css/bootstrap.min.css" rel="stylesheet">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
  <script type="text/javascript">
  //web sayfası yüklendiğinde script çalışmaya başlar
    $(document).ready(() => {
      var Socket
      //google chart default kodları
      google.charts.load('current', { 'packages': ['gauge'] });
      google.charts.setOnLoadCallback(drawChart);
      function drawChart() {
        //chart isimleri ve başlangıç değerleri
        var data = google.visualization.arrayToDataTable([
          ['Label', 'Value'],
          ['Tempature', 80],
          ['Humidity', 55],
        ]);
        //chart için gösterge değerleri
        var options = {
          redFrom: 90, redTo: 100,
          yellowFrom: 75, yellowTo: 90,
          minorTicks: 5
        };
        //web sayfasına chart yükleniyor
        var chart = new google.visualization.Gauge(document.getElementById('chart_div'));
        //ilk chart çiziliyor
        chart.draw(data, options);
        //web socket nesnesi oluşturuluyor
        Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
        //sockete bir mesaj geldiğince çalışacak olan fonksiyorn
        Socket.onmessage = function (event) {
          //gelen veri tire işareti ile parçalara ayrılıyor.
          //split fonksiyonu array döndürüyor.
          var parsedData = event.data.split("-");
          if (parsedData.length == 2) {
            //eğer sıcaklık bilgisi gelmiş ise chart güncelleniyor
            if (parsedData[0] == "sc") {
              data.setValue(0, 1, parsedData[1]);
              chart.draw(data, options);
            }
            //eğer nem bilgisi gelmiş ise chart güncelleniyor
            if (parsedData[0] == "hu") {
              data.setValue(1, 1, parsedData[1]);
              chart.draw(data, options);
            }
            //eğer buton bilgisi gelmiş ise ,
            if (parsedData[0].substring(0, 3) == "btn") {
              //btn2-1 son bsamağı 1 ise yani true buttonlar yeşil oluyor
              if (parsedData[1] == "1") {
                $("#" + parsedData[0]).removeClass();
                $("#" + parsedData[0]).addClass("btn btn-success btnType");
                $("#" + parsedData[0]).attr('value', 'true');
              }
              if (parsedData[1] == "0") {
                //btn2-0 son bsamağı 0 ise yani true buttonlar yeşil oluyor
                $("#" + parsedData[0]).removeClass();
                $("#" + parsedData[0]).addClass("btn btn-dark btnType");
                $("#" + parsedData[0]).attr('value', 'false');
              }
            }
          }
        }
      }
      //eğer btnType classına sahip tag'e tıklandığında çalışan fonksiyon
      $(document).on('click', '.btnType', function (event) {
        //buttonun value(bool) değerini alıyoruz
        var elm = $(this).attr('value');
        //eğer butonun şu anki değeri false ise koşula giriyor
        if (elm == 'false') {
          //alttaki 2 satır buttonun rengini değiştiriyor
          $(this).removeClass();
          $(this).addClass("btn btn-success btnType");
          //buttonun değerini falseden true'ye çekiyor
          $(this).attr('value', 'true');
          //socket ile servere buton durmunu gönderiyor (btn10-1)
          Socket.send($(this).attr('id') + "-1");
        }
        else if (elm == 'true') {
          //alttaki 2 satır buttonun rengini değiştiriyor
          $(this).removeClass();
          $(this).addClass("btn btn-dark btnType");
          //buttonun değerini falseden trueye çekiyor
          $(this).attr('value', 'false');
          //socket ile servere buton durmunu gönderiyor (btn10-0)
          Socket.send($(this).attr('id') + "-0");
        }
      });
    });
  </script>
  <title>Kontrol Paneli</title>
</head>

<body style="background: linear-gradient(to bottom right, #99ffc1 34%, #ffffff 95%);">
  <nav class="navbar navbar-expand-lg  navbar-dark bg-dark ">
    <span class="container">
    <a class="col navbar-brand text-light" href="#">Navbar</a>
    <form class="right" action="/logout" method="GET">
      <button class="btn btn-danger " type="submit" data-toggle="collapse" data-target="#navbarNav"
        aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
        <span class="">Çıkış</span>
      </button>
    </form>
  </span>
  </nav>
  <div class="container">
    <br>
    <div class="bg-dark rounded d-flex justify-content-center">
      <div id="chart_div"></div>
    </div>
    <div class="container ">
      </br>
      <p class="display-3 text-center">Anahtarlar </p>
      <div class="row display-15" style="text-align: center;">
        <div class="col ">
          <button type="button" style="width: 100%; " id="btn1" value="false" class="btn btn-dark btnType ">
            <p class=" lead" style="margin: 0px;"> Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn3" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button3</p>
          </button>
          <label>Açıklama 3</label>
          <button type="button" style="width: 100%; " id="btn5" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button5</p>
          </button>
          <label>Açıklama 5</label>
          <button type="button" style="width: 100%; " id="btn7" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button7</p>
          </button>
          <label>Açıklama 7</label>
          <button type="button" style="width: 100%; " id="btn9" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button9</p>
          </button>
          <label>Açıklama 9</label>
          <button type="button" style="width: 100%; " id="btn11" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button11</p>
          </button>
          <label>Açıklama 11</label>
          <button type="button" style="width: 100%; " id="btn13" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button13</p>
          </button>
          <label>Açıklama 13</label>
          <button type="button" style="width: 100%; " id="btn15" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button15</p>
          </button>
          <label>Açıklama 15</label>
        </div>
        <div class="col">
          <button type="button" style="width: 100%; " id="btn2" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button2</p>
          </button>
          <label>Açıklama 2</label>
          <button type="button" style="width: 100%; " id="btn4" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button4</p>
          </button>
          <label>Açıklama 4</label>
          <button type="button" style="width: 100%; " id="btn6" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button6</p>
          </button>
          <label>Açıklama 6</label>
          <button type="button" style="width: 100%; " id="btn8" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button8</p>
          </button>
          <label>Açıklama 8</label>
          <button type="button" style="width: 100%; " id="btn10" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button10</p>
          </button>
          <label>Açıklama 10</label>
          <button type="button" style="width: 100%; " id="btn12" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button12</p>
          </button>
          <label>Açıklama 12</label>
          <button type="button" style="width: 100%; " id="btn14" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button14</p>
          </button>
          <label>Açıklama 14</label>
          <button type="button" style="width: 100%; " id="btn16" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button16</p>
          </button>
          <label>Açıklama 16</label>

        </div>
      </div>
    </div>
  </div>
</body>
</html>
)=====";