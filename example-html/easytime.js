$ = function(el) { return document.querySelector(el) }
function easy_date(t) {
	let d = new Date(t)
	d.setHours(0,0,0)
	return d.valueOf()
}
function sind(x) {
	return Math.sin(Math.PI / 180 * x)
}
function cosd(x) {
	return Math.cos(Math.PI / 180 * x)
}
function unixtojulian(x) {
	return (x / 86400) + 2440587.5
}
function juliantounix(x) {
	return (x - 2440587.5) * 86400
}
function easy_solar_noon(longitude, date) {
	let n = unixtojulian(date) - 2451545 + 0.0008
	let jstar = n - longitude / 360
	let m = 357.5291 + 0.98560028 * jstar
	while (m > 360)
		m -= 360
	let c = 1.9148*sind(m) + 0.02*sind(2*m) + 0.0003*sind(3*m)
	let lambda = m + c + 180 + 102.9372
	while (lambda > 360)
		lambda -= 360
	return 2451545 + jstar + 0.0053*sind(m) - 0.0069*sind(2*lambda)
}
function easy_hour_angle(latitude, longitude, date) {
	let n = unixtojulian(date) - 2451545 + 0.0008
	let jstar = n - longitude / 360
	let m = 357.5291 + 0.98560028 * jstar
	while (m > 360)
		m -= 360
	let c = 1.9148*sind(m) + 0.02*sind(2*m) + 0.0003*sind(3*m)
	let lambda = m + c + 180 + 102.9372
	while (lambda > 360)
		lambda -= 360
	let delta = 180/Math.PI * Math.asin(sind(lambda)*sind(23.44))
	return 180/Math.PI * Math.acos((sind(-0.83) - sind(latitude)*sind(delta))
		/ (cosd(latitude)*cosd(delta)))
}
function easy_sunrise(latitude, longitude, date) {
	let offset = date % 86400
	let noon = easy_solar_noon(longitude, date-offset+86400/2)
	let hourangle = easy_hour_angle(latitude, longitude, date-offset+86400/2)
	return juliantounix(noon - hourangle / 360)
}
function easy_sunset(latitude, longitude, date) {
	let offset = date % 86400
	let noon = easy_solar_noon(longitude, date-offset+86400/2)
	let hourangle = easy_hour_angle(latitude, longitude, date-offset+86400/2)
	return juliantounix(noon + hourangle / 360)
}
function easy_time() {
	let now = Date.now()/1000
	let date = easy_date(now*1000)
	let latitude = $('#lat').value
	let longitude = $('#long').value
	let t1 = easy_sunrise(latitude, longitude, date/1000)
	let t2 = easy_sunset(latitude, longitude, date/1000)
	let night = false

	if (now < t1) { // it's before sunrise
		night = true
		t2 = t1 // sunrise is the new t2
		t1 = easy_sunset(latitude, longitude, easy_date(date - 80000*1000)/1000)
	} else if (now > t2) { // it's after sunset
		night = true
		t1 = t2 // sunset is the new t1
		t2 = easy_sunrise(latitude, longitude, easy_date(date + 92000*1000)/1000)
	}
	// Bread and butter equation right here:
	let easytime = (now - t1) / (t2 - t1) * 12

	let h = Math.floor((easytime + (night ? 18 : 6)) % 24)
	minsec = (easytime - Math.floor(easytime)) * 60
	let m = Math.floor(minsec)
	let s = Math.floor((minsec - m) * 60)

	$('#easytime').value = (""+h).padStart(2, '0') + ":"
		+ (""+m).padStart(2, '0') + ":"
		+ (""+s).padStart(2, '0')
}
