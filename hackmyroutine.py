#******************************************#
# LEYLA NOVINI MARCH 2016 CODE ADAPTED FROM#
# Tweet-a-Pot by Gregg Horton 2011         #
# *****************************************#

##Import Libraries

import twitter
import serial
import time
from time import mktime
from datetime import datetime

##authenticate yourself with twitter
api = twitter.Api(consumer_key='insert_unique_code', consumer_secret='insert_unique_code', access_token_key='insert_unique_code', access_token_secret='insert_unique_code')

##set to your serial port from arduino
ser = serial.Serial('insert_usb_port', 9600)

## check serial port
def checkokay():
	ser.flushInput()
	time.sleep(3)
	line=ser.readline()
	time.sleep(3)

	if line == ' ':
		line=ser.readline()
	print 'here'
## Welcome message
print 'Hack My Routine!'

def hackroutine():
	status = [] 
	x = 0
	
	status = api.GetUserTimeline('insert_twitterhandle') ##grab latest statuses

	checkIt = [s.text for s in status] ##put status in an array
	times = [s.created_at for s in status] ##put status in an array

	hack = checkIt[0].split() ##split first tweet into words
	my_time = times[0]
	print "%s" % my_time

	#convert twitter time to timestamp
	
	# get twitter created_at as python time struct
	ts = time.strptime(my_time,'%a %b %d %H:%M:%S +0000 %Y')
	print "%s" % ts
	
	# convert to datetime object
	dts = datetime.fromtimestamp(mktime(ts))
	print "%s" % dts

	# get current time as datetime
	now = datetime.now()
	
	# subtract
	diff = now - dts
	print "%s" % diff

	# get minute difference ??

	m = (diff.seconds / 60)-60
	print "%s" % m


	
	## check for match and write to serial if match
	if hack[0] == '#hackmyroutine' and m < 5:
		print 'Tweet Recieved, Turn off light!'
		ser.write('1')

	else:
		ser.write('0')
		print 'Awaiting Tweet'
        print '%s' % hack[0]
		
		
	
while 1:
	hackroutine() ## call hackroutine function
	time.sleep(15) ## sleep for 15 seconds to avoid rate limiting
	
