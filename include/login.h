#include "pgmspace.h"

char loginPageHtml[] PROGMEM = R"=====(
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-alpha3/dist/css/bootstrap.min.css" rel="stylesheet">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
  <script type="text/javascript">
    var Socket;
  </script>
  <title>Document</title>
</head>

<body style="background: linear-gradient(to bottom right, #99ffc1 34%, #ffffff 95%); ">
  <nav class="navbar navbar-expand-lg navbar-light bg-dark container">
    <a class="col navbar-brand text-light" href="#">Navbar</a>

    <div class="collapse navbar-collapse" id="navbarNav">
    </div>
  </nav>
  </br>
  </br>
  <div class="container" style="margin-top: 10%; ">
    <p class="display-1">Giriş Ekranı</p>
    <div class="row align-items-center">

      <div class="col col-md-8">
        <form action="/controlpanel" method="GET">
          <div class="form-group ">
            <label class="display-6" for="exampleInputEmail1">Email address :</label>
            <input type="text" class="form-control" id="exampleInputEmail1" name="fname" aria-describedby="emailHelp"
              placeholder="Enter email">
            <small id="emailHelp" class="form-text text-muted">We'll never share your email with anyone else.</small>
          </div>
          <div class="form-group">
            <label class="display-6" for="exampleInputPassword1">Password :</label>
            <input type="password" class="form-control" id="exampleInputPassword1" name="lname" placeholder="Password">
          </div>
          </br>
          <button type="submit" class="btn btn-primary">Submit</button>
        </form>
      </div>
    </div>
  </div>
  <form>
</body>
</html>
)=====";