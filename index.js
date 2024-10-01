window.onload = (event) => {
    
  };


  fetch('code_ex/C/ejPunterosRobot.c')
    .then(res => res.text())
    .then(res => {
      document.getElementById("ejPunterosRobot").innerHTML = res;
      $('#ejPunterosRobot').each(function(i, e) {hljs.highlightBlock(e);})
    }
    )