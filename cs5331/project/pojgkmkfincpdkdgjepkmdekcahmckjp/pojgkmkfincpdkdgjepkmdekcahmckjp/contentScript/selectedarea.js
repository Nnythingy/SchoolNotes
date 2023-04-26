var selectedarea, tempX, tempY, FinX, FinY, width, height, monitorTop, mid, last;

function calculate(e) {
    FinX = e.clientX > tempX ? tempX : e.clientX - 1, FinY = e.clientY > tempY ? tempY : e.clientY - 1, width = Math.abs(e.clientX - tempX), height = Math.abs(e.clientY - tempY), selectedarea.style.left = FinX + "px", selectedarea.style.top = FinY + "px", selectedarea.style.width = width + "px", selectedarea.style.height = height + "px"
}

function removeContainer() {
    chrome.runtime.sendMessage({
        method: "captured",
        left: FinX + 1,
        top: FinY + 1,
        width: width - 2,
        height: height - 2,
        devicePixelRatio: window.devicePixelRatio,
        title: document.title,
        service: window.service,
        websiteUrl: window.location.href
    }), monitorStop(), grabStop(), watchStop(), window.location.reload()
}

function createSelectionContainer(e) {
    selectedarea && selectedarea.parentNode && selectedarea.parentNode.removeChild(selectedarea), e.stopPropagation(), e.preventDefault(), tempX = e.clientX, tempY = e.clientY, (selectedarea = document.createElement("div")).setAttribute("class", "selection-container"), document.addEventListener("mousemove", calculate, !1), document.addEventListener("mouseup", removeContainer, !1), document.body.appendChild(selectedarea)
}

function mouseMoveCalculate(e) {
    monitorTop.style.width = e.clientX + "px", mid.style.height = e.clientY + "px"
}

function grabStart() {
    document.addEventListener("mousedown", createSelectionContainer, !1)
}

function grabStop() {
    document.removeEventListener("mousedown", createSelectionContainer, !1), document.removeEventListener("mousemove", calculate, !1), document.removeEventListener("mouseup", removeContainer, !1), selectedarea && selectedarea.parentNode && selectedarea.parentNode.removeChild(selectedarea)
}

function monitorStart() {
    (monitorTop = document.createElement("div")).setAttribute("class", "monitor-top"), document.body.appendChild(monitorTop), (mid = document.createElement("div")).setAttribute("class", "monitor-mid"), document.body.appendChild(mid), (last = document.createElement("div")).setAttribute("class", "monitor-last"), document.body.appendChild(last), document.addEventListener("mousemove", mouseMoveCalculate, !1)
}

function monitorStop() {
    document.removeEventListener("mousemove", mouseMoveCalculate, !1), monitorTop && monitorTop.parentNode && monitorTop.parentNode.removeChild(monitorTop), mid && mid.parentNode && mid.parentNode.removeChild(mid), last && last.parentNode && last.parentNode.removeChild(last)
}

function escFunc(e) {
    27 === e.keyCode && (monitorStop(), grabStop(), watchStop())
}

function watchStart() {
    document.addEventListener("keydown", escFunc, !1)
}

function watchStop() {
    document.removeEventListener("keydown", escFunc, !1)
}
try {
    monitorStop(), grabStop(), watchStop()
} catch (e) {}
grabStart(), monitorStart(), watchStart();