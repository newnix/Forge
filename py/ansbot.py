#!/usr/bin/env python

## This is meant to be a bot for the Ask Noah! Show, in which 
## the bot can keep track of topic requests and either emails them to the show address
## or just stores them in a database to be displayed upon request

## This imports a few things to get the bot framework set up
import telepot
from pprint import pprint 
from telepot.loop import MessageLoop
import sys
import time

## here's where we define which bot is ours
bot = telepot.Bot('426960720:AAGCuthrFGenO1HZ2Gk9W6LKgUdB4OPDVp8')

## apparently this is the python way of doing switch statements
dict commands = { '/help' : tg_help,
                 '/showtopics' : topic_show,
                 '/addtopic' : topic_add,
                 '/rmtopic' : topic_remove,
                 '/getphone' : tg_prntphone,
                 '/getemail' : tg_prntemail,
                 '/reportbug' : tg_sndbug } 

def parsecmd(msg):
    ## This is where we decide if there's even a command being passed
    ## supported commands are:
    # /help - display list of commands
    # /showtopics - display the current topic list
    # /addtopic - add a topic suggestion
    # /rmtopic - delete a comment suggestion (should check UID)
    # /getphone - display the ANS hotline number
    # /getemail - display the ANS feedback email inbox
    # /reportbug - tell me something's wrong
    list words = []
    if ( msg['text'][0] == '/' ):

    
## This is the recommended way to handle the incoming messages, so you don't need to worry about 
## maintaining the offset while fetching new data
def handle(msg):
    content_type, chat_type, chat_id = telepot.glance(msg)
    print(content_type, chat_type, chat_id)

    ## this is how the command is likely to show up
    if content_type == 'text':
        bot.sendMessage(chat_id, msg['text'])
        bot.sendMessage(chat_id, msg['user_id'])

#TOKEN = sys.argv[1] # meant to get the token from the command lin

MessageLoop(bot,handle).run_as_thread()
print('Listening...')

# used to keep the bot alive
while 1:
    time.sleep(10)
