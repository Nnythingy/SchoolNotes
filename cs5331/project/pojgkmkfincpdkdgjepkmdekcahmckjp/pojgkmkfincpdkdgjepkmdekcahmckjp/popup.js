(()=>{"use strict";var e,n={6699:(e,n,t)=>{t.d(n,{Z:()=>h});var o=t(3645),r=t.n(o),i=t(1667),a=t.n(i),c=t(2794),s=t(9543),l=t(5975),d=r()((function(e){return e[1]}));d.push([e.id,"@import url(https://fonts.googleapis.com/css2?family=Noto+Sans:wght@400;700&display=swap);"]);var m=a()(c),p=a()(s),g=a()(l);d.push([e.id,".App {\n  text-align: center;\n\n  /* @font-face { \n    font-family: 'Metropolis';\n    font-weight: 700;\n    src: local('Metropolis'), url(./fonts/Metropolis-Bold.otf) format('opentype');\n  };\n\n  @font-face {\n    font-family: 'Metropolis';\n    font-weight: 500;\n    src: local('Metropolis'), url(./fonts/Metropolis-Medium.otf) format('opentype');\n  };  */\n\n  font-family: 'MetropolisRegular';\n  height: 0rem;\n  background: rgb(34, 34, 34);\n  font-size: 12px;\n  width: auto;\n  overflow: visible;\n  margin-bottom: 2px;\n}\n\n\n\n.App-logo {\n  /* height: 40vmin; */\n  pointer-events: none;\n}\n\n@media (prefers-reduced-motion: no-preference) {\n  .App-logo {\n    animation: App-logo-spin infinite 20s linear;\n  }\n}\n\n.App-header {\n  background-color: #282c34;\n  min-height: 100vh;\n  display: flex;\n  flex-direction: column;\n  align-items: center;\n  justify-content: center;\n  font-size: calc(10px + 2vmin);\n  color: white;\n}\n\n.App-link {\n  color: #61dafb;\n}\n\nbody {\n  margin: 0;\n  padding: 0;\n}\n\n@keyframes App-logo-spin {\n  from {\n    transform: rotate(0deg);\n  }\n\n  to {\n    transform: rotate(360deg);\n  }\n}\n\n.icon1 {\n  display: block;\n  width: 41px;\n  height: 40px;\n  float: left;\n  margin: 0 5px 0 0;\n  background: url("+m+") center/contain no-repeat;\n}\n\n.icon2 {\n  display: block;\n  width: 58px;\n  height: 40px;\n  float: left;\n  margin: 0 5px 0 0;\n  background: url("+p+") center/contain no-repeat;\n}\n\n.buttonloading {\n  width: 148px;\n}\n\n.icon3 {\n  display: block;\n  width: 30px;\n  height: 40px;\n  float: left;\n  margin: 0 5px 0 0;\n  background: url("+g+') center/contain no-repeat;\n}\n\n.description {\n  /* color: slategrey; */\n  margin: 0.5rem 0px;\n  font-size: 0.75rem;\n  padding: 1rem 1rem;\n  box-shadow: 0px 0px 3px grey;\n  /* display: flex; */\n  align-items: center;\n  justify-content: center;\n  border: none;\n  width: "7rem";\n  /* height: 2rem; */\n  /* background: #e02029; */\n  cursor: pointer;\n  border-radius: 13px;\n  /* font-family: "MetropolisRegular"; */\n  font-weight: bold;\n  color: #fff;\n  margin: 0.5rem 5px;\n  font-size: 15px;\n  padding: 0.2rem 0.2rem;\n  font-family: inherit;\n  padding: 10px 10px;\n  width: 180px;\n  color: #708090;\n}\n\n.description h2 {\n  padding: 10px;\n}',""]);const h=d},5043:(e,n,t)=>{var o=t(3935),r=t(7294),i=t(3379),a=t.n(i),c=t(6699);a()(c.Z,{insert:"head",singleton:!1}),c.Z.locals;var s=t(8804),l=(t(9957),t(888)),d=t(7625),m=t(1436),p=t(3530),g=t(5477);const h=s.ZP.div`
  // width: 10rem;
  box-shadow: 0 0 1rem #ccc;

  min-height: 14rem;
  /* max-height: 16rem; */

  padding: 1.5rem;
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  align-items: flex-start;

  background: ${e=>e.mode?"#222":"#FFF"};
  color: ${e=>e.mode?"#FFF":"#000"};

  h1 {
    font-family: 'MetropolisRegular';
    font-weight: 700;
    font-size: 1.5rem;
  }

  h2 {
    font-family: 'MetropolisRegular';
    font-weight: 500;
    font-size: 1rem;
    margin: 0;
  }  

  form {
    display: flex;
    align-items: center;
  }

  input {
    margin: 0;
    height: 1.5rem;
    border-radius: 0.5rem;
    max-width: 80%;
    margin-left: 0.5rem;
    border: 1px solid #333;
  }

  p {
    text-align: left;
    margin: 0;
  }
`,f=s.ZP.div`
  border-bottom: 1px solid #ccc;
  height: 1px;
  width: 100%;

  margin: 1rem 0;
`,u=s.ZP.div`
  width : 100%;
  display: flex;
  align-items: center;
  justify-content : space-between;
  .custom-classname.react-toggle--checked .react-toggle-track {
   background-color: #fff;
  }

  margin: ${e=>e.spaced?"1rem 0 0 0":"0"};
`;s.ZP.div`
    display: flex;
    align-items: center;
    justify-content: space-evenly;
    width: 100%;
`,s.ZP.button`
  width: 1rem;
  height: 1rem;

  border: none;

  background: ${e=>e.checked?"#E50914":"#ccc"};
  cursor: pointer;

  display: flex;
  align-items: center;
  justify-content: center;
`,s.ZP.div`
    width: 100%;
    height: 1px;
    border-top: 1px solid #ccc;
    margin: 1rem 0;

    h2 {
        font-family: 'MetropolisRegular';
        font-size: 1.25rem;
        margin-top:-0.8rem;
        margin-left: 5rem;
        width: 3rem;

        text-align: center;
        color: ${e=>e.mode?"#FFF":"#222"};
        background: ${e=>e.mode?"#222":"#FFF"};
    }
`;const w=document.createElement("div");document.body.appendChild(w),o.render(r.createElement((function(){(0,r.useEffect)((()=>{window.chrome.storage.sync.get(null,(e=>{e.darkmode&&n(!0)})),window.chrome.tabs.query({currentWindow:!0,active:!0},(function(e){var n=e[0].url;window.chrome.tabs.sendMessage(e[0].id,{text:"check for frameset?"},(function(e){"yes"==(e=e||{}).status&&(o(!0),b(!0))})),n.includes("file://")&&window.chrome.extension.isAllowedFileSchemeAccess((function(n){if(n)try{window.chrome.tabs.sendMessage(e[0].id,{text:"are_you_there_content_script?"},(function(n){if("yes"!=(n=n||{}).status)for(let n=0;n<window.chrome.runtime.getManifest().content_scripts[0].js.length;n++){let t=window.chrome.runtime.getManifest().content_scripts[0].js[n];e[0].id&&window.chrome.tabs.executeScript(e[0].id,{file:t},(e=>{const n=window.chrome.runtime.lastError;n&&console.error(JSON.stringify(n))}))}}))}catch(e){}else a(!0),o(!0)})),(n.includes("chrome://")||n.includes("chrome-extension:")||n.includes("https://chrome.google.com"))&&o(!0)}))}),[]);const[e,n]=(0,r.useState)(!1),[t,o]=(0,r.useState)(!1),[i,a]=(0,r.useState)(!1),[c,s]=(0,r.useState)(!1),[w,x]=(0,r.useState)(!1),[y,b]=(0,r.useState)(!1);return r.createElement("div",{className:"App"},t?r.createElement(h,{mode:e},y?r.createElement("h1",{style:{color:"red",fontWeight:70}},"Screenshotting does not work on website containing frameset due to security reasons."):i?r.createElement("div",{style:{width:"170px"}},r.createElement("h2",null,"File access needed "),r.createElement("h4",null,"Please go to your browser’s extension settings and enable “Allow access to file URLs”, so the extension can access this page."),r.createElement(p.Z,{variant:"contained",size:"small",color:"secondary",onClick:e=>{window.chrome.tabs.create({url:"chrome://extensions/?id="+window.chrome.runtime.id})}},"Extension Settings")):r.createElement("h1",{style:{color:"red",fontWeight:70}},"Screenshotting does not work on chrome internal pages and extensions gallery"),r.createElement(u,null,r.createElement(l.Z,{id:"cheese-status",defaultChecked:e,className:"custom-classname",icons:{unchecked:r.createElement(d.G,{size:"xs",color:"#FFFF00",icon:m.enB}),checked:r.createElement(d.G,{size:"xs",color:"#222",icon:m.DBF})},onChange:()=>{n(!e),window.chrome.storage.sync.set({darkmode:!e})}}),r.createElement("label",{htmlFor:"cheese-status"},"Theme: Dark/Light"))):r.createElement(h,{mode:e},r.createElement("div",{style:{display:"flex",justifyContent:"space-between",width:"550px"}},w?r.createElement(p.Z,{variant:"contained",color:"secondary"},r.createElement("span",{className:"buttonloading"},r.createElement(g.Z,{style:{width:"30px",height:"30px",color:"white"}}))):r.createElement(p.Z,{variant:"contained",color:"secondary",onClick:e=>{x(!0),window.chrome.tabs.query({currentWindow:!0,active:!0},(function(e){var n=e[0];window.chrome.tabs.sendMessage(n.id,{from:"visible_area"})}))}},r.createElement("span",{className:"icon1"}),r.createElement("span",null,window.chrome.i18n.getMessage("visibleButtonTitle"))),c?r.createElement(p.Z,{variant:"contained",color:"secondary"},r.createElement("span",{className:"buttonloading"},r.createElement(g.Z,{style:{width:"30px",height:"30px",color:"white"}}))):r.createElement(p.Z,{variant:"contained",color:"secondary",onClick:e=>{s(!0),window.chrome.tabs.query({currentWindow:!0,active:!0},(function(e){var n=e[0];window.chrome.tabs.sendMessage(n.id,{from:"full_page"})}))}},r.createElement("span",{className:"icon2"}),r.createElement("span",null,window.chrome.i18n.getMessage("fullButtonTitle")," ")),r.createElement(p.Z,{variant:"contained",color:"secondary",onClick:e=>{window.chrome.tabs.query({currentWindow:!0,active:!0},(function(e){var n=e[0];window.chrome.tabs.sendMessage(n.id,{from:"show_selection_area"})})),setTimeout((()=>{window.close()}),300)}},r.createElement("span",{className:"icon3"}),r.createElement("span",null,window.chrome.i18n.getMessage("specificButtonTitle")))),r.createElement("div",{style:{marginTop:"10px",display:"flex",justifyContent:"space-between",width:"550px"}},r.createElement("div",{className:"description",style:{padding:"0px 5px"}},r.createElement("h2",{style:{marginBottom:"0px",color:"dimgrey"}},window.chrome.i18n.getMessage("visibleAreaTitle")),r.createElement("p",{style:{margin:"10px"}},window.chrome.i18n.getMessage("visibleAreaDesc"))),r.createElement("div",{className:"description",style:{padding:"0px 5px"}},r.createElement("h2",{style:{marginBottom:"0px",color:"dimgrey"}},window.chrome.i18n.getMessage("fullpageTitle")),r.createElement("p",{style:{margin:"10px"}},window.chrome.i18n.getMessage("fullpageDesc"))),r.createElement("div",{className:"description",style:{padding:"0px 5px"}},r.createElement("h2",{style:{marginBottom:"0px",color:"dimgrey"}},window.chrome.i18n.getMessage("specificAreaTitle")),r.createElement("p",{style:{margin:"10px"}},window.chrome.i18n.getMessage("specificAreaDesc")))),r.createElement(f,null),r.createElement(u,null,r.createElement("div",{style:{display:"flex",alignItems:"center"}},r.createElement(l.Z,{id:"cheese-status",defaultChecked:e,className:"custom-classname",icons:{unchecked:r.createElement(d.G,{size:"xs",color:"#FFFF00",icon:m.enB}),checked:r.createElement(d.G,{size:"xs",color:"#222",icon:m.DBF})},onChange:()=>{n(!e),window.chrome.storage.sync.set({darkmode:!e})}}),r.createElement("label",{htmlFor:"cheese-status"},"Theme: Dark/Light")))))}),null),w)},5975:(e,n,t)=>{e.exports=t.p+"fb7f4b44bffec5bbbf5c.svg"},2794:(e,n,t)=>{e.exports=t.p+"e69ad413c325b8fcd602.png"},9543:(e,n,t)=>{e.exports=t.p+"49b3c276a6fa9b0f899f.png"}},t={};function o(e){var r=t[e];if(void 0!==r)return r.exports;var i=t[e]={id:e,exports:{}};return n[e](i,i.exports,o),i.exports}o.m=n,e=[],o.O=(n,t,r,i)=>{if(!t){var a=1/0;for(l=0;l<e.length;l++){for(var[t,r,i]=e[l],c=!0,s=0;s<t.length;s++)(!1&i||a>=i)&&Object.keys(o.O).every((e=>o.O[e](t[s])))?t.splice(s--,1):(c=!1,i<a&&(a=i));c&&(e.splice(l--,1),n=r())}return n}i=i||0;for(var l=e.length;l>0&&e[l-1][2]>i;l--)e[l]=e[l-1];e[l]=[t,r,i]},o.n=e=>{var n=e&&e.__esModule?()=>e.default:()=>e;return o.d(n,{a:n}),n},o.d=(e,n)=>{for(var t in n)o.o(n,t)&&!o.o(e,t)&&Object.defineProperty(e,t,{enumerable:!0,get:n[t]})},o.g=function(){if("object"==typeof globalThis)return globalThis;try{return this||new Function("return this")()}catch(e){if("object"==typeof window)return window}}(),o.o=(e,n)=>Object.prototype.hasOwnProperty.call(e,n),(()=>{var e;o.g.importScripts&&(e=o.g.location+"");var n=o.g.document;if(!e&&n&&(n.currentScript&&(e=n.currentScript.src),!e)){var t=n.getElementsByTagName("script");t.length&&(e=t[t.length-1].src)}if(!e)throw new Error("Automatic publicPath is not supported in this browser");e=e.replace(/#.*$/,"").replace(/\?.*$/,"").replace(/\/[^\/]+$/,"/"),o.p=e})(),(()=>{var e={42:0};o.O.j=n=>0===e[n];var n=(n,t)=>{var r,i,[a,c,s]=t,l=0;for(r in c)o.o(c,r)&&(o.m[r]=c[r]);if(s)var d=s(o);for(n&&n(t);l<a.length;l++)i=a[l],o.o(e,i)&&e[i]&&e[i][0](),e[a[l]]=0;return o.O(d)},t=self.webpackChunkscreenshotting=self.webpackChunkscreenshotting||[];t.forEach(n.bind(null,0)),t.push=n.bind(null,t.push.bind(t))})();var r=o.O(void 0,[758,714],(()=>o(5043)));r=o.O(r)})();