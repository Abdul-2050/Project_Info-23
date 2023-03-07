const char index_html[] =
R"=====(


<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
     #rect {
    position: absolute;
    width: 50px;
    height: 100px;
    background-color: greenyellow;
    border: 1px solid black;
    border-radius: 10px;
    box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.3);
    top: 0;
  }

  body{
    background-color:  rgb(88, 190, 199);
  }

  </style>
</head>
<body>
  <div id="rect"></div>



</body>

<script>
  const rect = document.getElementById('rect');
  let topPos = 0;

  document.addEventListener('keydown', (event) => {
    if (event.code === 'ArrowUp') {
      topPos -= 10;
    } else if (event.code === 'ArrowDown') {
      topPos += 10;
    }
    rect.style.top = `${topPos}px`;
  });


  var count = 1;

 setInterval(function checkButtonStatus() {
  var xhr = new XMLHttpRequest();
xhr.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
    var response = JSON.parse(this.responseText);
    if (response.buttonPressed) {
      topPos += 10;
      rect.style.top = `${topPos}px`;
      //document.getElementById("message").innerHTML = "Button is pressed"+ count;
    } else {
      //document.getElementById("message").innerHTML = "Button is not pressed!";
    }
  }
};
xhr.open("GET", "/checkButtonStatus", true);
xhr.send();
}, 10); 


</script>

</html>

)=====";
