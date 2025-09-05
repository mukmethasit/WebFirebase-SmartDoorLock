// alert("HI App.js")
function redirectToIndex() {
    window.location.href = 'index.html'
}

function redirectTofontinfo() {
    window.location.href = 'fontinfo.html'
}

function redirectTofont() {
  window.location.href = 'font.html'
}

function redirectTobutton1() {
  window.location.href = 'button1.html'
}

function redirectToinsert() {
  window.location.href = 'insert.html'
}

function togglePasswordVisibility() {
  var passwordInput = document.getElementById('password');
  // If the checkbox is checked, change the type to 'text' to show the password
  if (passwordInput.type === "password") {
    passwordInput.type = "text";
  } else {
    // Otherwise, change it back to 'password' to hide the password
    passwordInput.type = "password";
  }
}

function alertLog(){
  alert("Wrong Room & Password");
}



