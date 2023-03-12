

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
      setInterval(() => {
  const xhr = new XMLHttpRequest();
  xhr.onreadystatechange = () => {
    if (xhr.readyState === 4 && xhr.status === 200) {
      const data = parseInt(xhr.responseText);
      // do something with the received integer data
      document.getElementById("counting").innerHTML = " #" + data;
    }
  };
  xhr.open('GET', '/data');
  xhr.send();
}, 10);
    </script>
  </body>
</html>








)#####";