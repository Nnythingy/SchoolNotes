"document.getElementById('frame1').contentWindow.postMessage(document.getElementById('bing').checked?JSON.stringify({'search_engine':document.getElementById('bing').value,'content':document.getElementById('text1').value}):JSON.stringify({'search_engine':document.getElementById('google').value,'content':document.getElementById('text1').value}),'*');"