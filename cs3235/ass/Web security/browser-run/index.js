const puppeteer = require('puppeteer');

if(process.argv.length < 4){
	console.log("Missing arguments");
	process.exit(1);
}


try{
	timeout = parseInt(process.argv[2]);
} catch(e){
	timeout = 0;
}

(async () => {
	const browser = await puppeteer.launch(
        {
            executablePath: '/usr/bin/chromium',
            dumpio: true,
            args: ['--no-sandbox', '--disable-setuid-sandbox',
            '--disable-gpu', '--disable-software-rasterizer', '--headless']
        }
    );
	var i;
	for(i = 3; i < process.argv.length; i ++){
		const url = process.argv[i];
		console.log('URL: ' + url);
	
		const page = await browser.newPage();
		const resp = await page.goto(url, { timeout: timeout, waitUntil: "networkidle0" });
		console.log('Actual URL: ' + page.url());
		console.log('Status code: ' + resp.status());

		// from https://stackoverflow.com/a/59919144
		page
			.on('console', message =>
				console.log(`${message.type().substr(0, 3).toUpperCase()} ${message.text()}`))
				.on('pageerror', ({ message }) => console.log(message))
				.on('response', response =>
					console.log(`${response.status()} ${response.url()}`))
				.on('requestfailed', request =>
					console.log(`${request.failure().errorText} ${request.url()}`))
	}

	await browser.close();
})();
