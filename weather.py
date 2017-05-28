import subprocess
import pyowm
import time
area = 'Chennai,IN'
key = '9ee5ef38773143ed8056f7ba2573c6f8'
owm = pyowm.OWM(key)
obs=owm.weather_at_place(area)
w=obs.get_weather()
temp = w.get_temperature('celsius')['temp']
humidity = w.get_humidity()
report = 'The temperatur is' + str(temp) + 'degree Celsisus and Humidity is' + str(humidity) + 'Percenage'
subprocess.check_output(['espeak',report])
if temp > 28:
 subprocess.check_output(['espeak','Its a hot day Chief'])

