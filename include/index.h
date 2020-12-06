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
    $(document).ready(() => {
      var Socket
      var btn1 = false;
      google.charts.load('current', { 'packages': ['gauge'] });
      google.charts.setOnLoadCallback(drawChart);
      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['Label', 'Value'],
          ['Tempature', 80],
          ['Humidity', 55],
        ]);
        var options = {

          redFrom: 90, redTo: 100,
          yellowFrom: 75, yellowTo: 90,
          minorTicks: 5
        };
        var chart = new google.visualization.Gauge(document.getElementById('chart_div'));
        chart.draw(data, options);
        Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
        Socket.onmessage = function (event) {
          console.log(event.data);
          var parsedData = event.data.split("-");

          if (parsedData.length == 2) {
            if (parsedData[0] == "sc") {
              data.setValue(0, 1, parsedData[1]);
              chart.draw(data, options);
            }
            if (parsedData[0] == "hu") {
              data.setValue(1, 1, parsedData[1]);
              chart.draw(data, options);
            }

            if (parsedData[0].substring(0, 3) == "btn") {
              if (parsedData[1] == "1") {
                $("#" + parsedData[0]).removeClass();
                $("#" + parsedData[0]).addClass("btn btn-success btnType");
                $("#" + parsedData[0]).attr('value', 'true');
              }
              if (parsedData[1] == "0") {
                $("#" + parsedData[0]).removeClass();
                $("#" + parsedData[0]).addClass("btn btn-dark btnType");
                $("#" + parsedData[0]).attr('value', 'false');
              }
            }
          }
        }
      }
      function sendText() {
        Socket.send(document.getElementById("txBar").value);
        document.getElementById("txBar").value = "";
      }
      $(document).on('click', '.btnType', function (event) {
        var elm = $(this).attr('value');
        if (elm == 'false') {
          $(this).removeClass();
          $(this).addClass("btn btn-success btnType");
          $(this).attr('value', 'true');
          Socket.send($(this).attr('id') + ":1");
        }
        else if (elm == 'true') {
          $(this).removeClass();
          $(this).addClass("btn btn-dark btnType");
          $(this).attr('value', 'false');
          Socket.send($(this).attr('id') + ":0");
        }
      });
    });
  </script>
  <title>Document</title>
</head>

<body style="background: linear-gradient(to bottom right, #99ffc1 34%, #ffffff 95%);">
  <nav class="navbar navbar-expand-lg navbar-light bg-dark container">
    <a class="col navbar-brand text-light" href="#">Navbar</a>
    <form action="/login" method="GET">
      <button class="btn btn-danger" type="submit" data-toggle="collapse" data-target="#navbarNav"
        aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
        <span class="">Log Out</span>
      </button>
    </form>
    <div class="collapse navbar-collapse" id="navbarNav">
    </div>
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
          <button type="button" style="width: 100%; " id="btn2" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn3" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn4" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn5" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn6" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn7" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn8" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
        </div>
        <div class="col">
          <button type="button" style="width: 100%; " id="btn9" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn10" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn11" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn12" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn13" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn14" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn15" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>
          <button type="button" style="width: 100%; " id="btn16" value="false" class="btn btn-dark btnType">
            <p class=" lead" style="margin: 0px;">Button1</p>
          </button>
          <label>Açıklama 1</label>

        </div>
      </div>
    </div>
  </div>
</body>

</html>
)=====";