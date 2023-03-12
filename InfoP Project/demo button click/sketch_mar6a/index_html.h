

const char index_html[] = 
R"#####(

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
       h1, p{
        display: flex;
        justify-content: center;
        justify-items: center;
        font-size: 50px;
        font-family: 'Courier New', Courier, monospace;
        border: 1px solid red;
        border-radius: 2px;
        text-align: center;
        font-weight: bold;
        color: greenyellow;
      } 

      body{
        background-color: black;
      }

      #counting{
        color:  rgb(49, 155, 190);
      }

    </style>
  </head>
  <body>
    <h1>Hello World!</h1>
    <p id="message">Button is not Pressed <span id="counting">#</span></p>

    <script>
      var count = 1;

      setInterval(function() {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            var response = JSON.parse(this.responseText);
            if (response.buttonPressed) {
              count = count + 1;
              //document.getElementById("message").innerHTML = "Button is pressed";
              document.getElementById("counting").innerHTML = " #" + count;
            } else {
              document.getElementById("message").innerHTML = "Button is not pressed!";
            }
          }
        };
        xhr.open("GET", "/checkButtonStatus", true);
        xhr.send();
      }, 10);
    </script>
  </body>
</html>








)#####";