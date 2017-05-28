import os
import subprocess
import mraa
import time
import pyaudio
import wave
import pocketsphinx as ps
import sphinxbase

LED_GPIO =10
onled=mraa.Gpio(LED_GPIO)
onled.dir(mraa.DIR_OUT)
onled.write(0)

LMD   = "/Skull/6838/6838.lm"
DICTD = "/Skull/6838/6838.dic"
CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 16000
RECORD_SECONDS = 2
PATH = 'output'
    
def decodeSpeech(speech_rec, wav_file):
	wav_file = file(wav_file,'rb')
	wav_file.seek(44)
	speech_rec.decode_raw(wav_file)
	result = speech_rec.get_hyp()
	return result[0]

def main():
     
    if not os.path.exists(PATH):
        os.makedirs(PATH)

    p = pyaudio.PyAudio()
    speech_rec = ps.Decoder(lm=LMD, dict=DICTD)

    while True:
        # Record audio
    	stream = p.open(format=FORMAT, channels=CHANNELS, rate=RATE, input=True, frames_per_buffer=CHUNK)
    	print("* recording")
    	frames = []
    	for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
    		data = stream.read(CHUNK)
    		frames.append(data)
    	print("* done recording")
    	stream.stop_stream()
    	stream.close()
    	        
        fn = "o.wav"
    	wf = wave.open(os.path.join(PATH, fn), 'wb')
    	wf.setnchannels(CHANNELS)
    	wf.setsampwidth(p.get_sample_size(FORMAT))
    	wf.setframerate(RATE)
    	wf.writeframes(b''.join(frames))
    	wf.close()

     	wav_file = os.path.join(PATH, fn)
    	recognised = decodeSpeech(speech_rec, wav_file)
    	rec_words = recognised.split()    	
       # print(str(rec_words))
        if "MAIL" in rec_words :
            subprocess.check_output(['python','/Skull/gmail.py'])
		if "WEATHER" in rec_words :
			subprocess.check_output('python', '/Skull/weather.py'])

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print "Keyboard interrupt received. Cleaning up..."
        
