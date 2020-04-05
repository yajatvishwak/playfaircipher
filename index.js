$("form.form1").submit(function (e) {
  e.preventDefault();
  var message = $("#message").val().toLowerCase().trim();
  var key = $("#key").val().toLowerCase().trim();
  var type = $("#type").val();

  var data = JSON.stringify({ type, key, message });
  if (message == "" || type == "" || key == "") {
    alert("Please Fill All Fields");
  } else {
    handleClick(data, type, message, key);
  }
  return false;
});

function isLetter(str) {
  return str.length === 1 && str.match(/[a-z]/i);
}

function handleClick(data, type, message, key) {
  console.log(data);
  fetch("http://localhost:3000/", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: data,
  })
    .then((response) => {
      return response.json();
    })
    .then((data) => {
      var out = data.output;
      var o = "";
      for (let i = 0; i < out.length; i++) {
        if (isLetter(out[i])) {
          o += out[i];
        }
      }
      if (message.length != o.length) {
        o = o.substr(0, message.length);
      }
      if (type == 1) {
        var fa = "The Encrypted Text is " + o;
        console.log(fa);
        document.getElementById("p1").innerHTML = fa;
      } else if (type == 2) {
        var fa = "The Decrypted Text is " + o;
        console.log(fa);
        document.getElementById("p1").innerHTML = fa;
      } else {
      }
    });
}
