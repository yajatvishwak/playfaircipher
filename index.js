$("form.form1").submit(function (e) {
  e.preventDefault();
  var message = $("#message").val().toLowerCase().trim();
  var key = $("#key").val().toLowerCase().trim();
  var type = $("#type").val();

  var data = JSON.stringify({ type, key, message });
  if (message == "" || type == "" || key == "") {
    alert("Please Fill All Fields");
  } else {
    handleClick(data);
  }
  return false;
});

function handleClick(data) {
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
      console.log(data);
      document.getElementById("p1").innerHTML = data.output;
    });
}
