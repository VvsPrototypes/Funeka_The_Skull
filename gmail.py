import subprocess
def gmail_checker(username,password):
    import imaplib,re
    i=imaplib.IMAP4_SSL('imap.gmail.com')
    try:
        i.login(username,password)
        x,y=i.status('INBOX','(MESSAGES UNSEEN)')
        messages=str(re.search('MESSAGES\s+(\d+)',y[0]).group(1))
        unseen=str(re.search('UNSEEN\s+(\d+)',y[0]).group(1))
        return (messages,unseen);
    except:
        return False,0
messages,unseen=gmail_checker('username@gmail.com','password')
print "%s messages, %s unseen" %(messages,unseen)
report = 'You have '+unseen+' un read e mails chief'
subprocess.check_output(['espeak',report])
