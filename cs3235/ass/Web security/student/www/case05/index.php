<?php 
header("X-XSS-Protection: 0");
?>
<HTML>
        <h1>Case 05</h1>
        <body>
                <p>Bonjour</p>
                <SCRIPT>
                        var pos = document.URL.indexOf("say=") + 4;
                        if (pos != 3){
								document.write("You said:</br>");
                                document.write(unescape(document.URL.substring(pos, document.URL.length)));
                        }

                </SCRIPT>
				</br>
                <span id="container"></span>! Welcome to our system <br/><br/>

                <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="get">
                        <p>Say what you want to say: </p>
						<textarea name="say" rows="10" cols="50"></textarea>
                        <input type="submit" />
                </form>
        </body>
</HTML>
