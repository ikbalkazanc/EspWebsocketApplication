#include "pgmspace.h"

char unauthorizePage[] PROGMEM = R"=====(
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-alpha3/dist/css/bootstrap.min.css" rel="stylesheet">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
  <title>Error</title>
</head>
<body style="background: linear-gradient(to bottom right, #99ffc1 34%, #ffffff 95%); ">
    <br>
    <div class="alert alert-danger" style="margin: 2%" role="alert">
        Bu sayfaya giriş izniniz yetkiniz yok. 
      </div>
      <div class="container">
      <form method="GET" action="/login">
        <button class="btn btn-warning">
            Giriş sayfasına gerçiş yap.
        </button>
      </form>
    </div>
</body>
</html>
)=====";