from __future__ import unicode_literals
import pprint
from urllib.parse import parse_qs
import webbrowser
import pickle
from datetime import datetime, timedelta
import time
import requests
from random import randint, choice

import vk


def get_auth_params():
    auth_url = ("https://oauth.vk.com/authorize?client_id={app_id}"
                "&scope=groups&revoke=1&redirect_uri=http://oauth.vk.com/blank.html"
                "&display=page&response_type=token".format(app_id=ид приложения))
    webbrowser.open_new_tab(auth_url)
    redirected_url = input("Paste here url you were redirected:\n")
    aup = parse_qs(redirected_url)
    aup['access_token'] = aup.pop(
        'https://oauth.vk.com/blank.html#access_token')
    save_auth_params(aup['access_token'][0], aup['expires_in'][0],
                     aup['user_id'][0])
    return aup['access_token'][0], aup['user_id'][0]

AT = строчка токена
#session = vk.Session()
#session = vk.AuthSession(app_id='ид приложения', user_login='логин', user_password='пароль') #разкомментировать для получения токена
session = vk.Session(access_token = AT)
api = vk.API(session)
#get_auth_params() #разкомментировать для получния токена
#exit(0) #разкомментировать для получния токена
capcha_sleep = 1
captcha_key = -1
false_key = False
while True:
    time.sleep(0.3)
    if randint(100, 200) == 179:
        print("I am working")
    try:
        if captcha_key != -1:
            First = api.board.getComments(group_id='30666517', topic_id='25736069', count=1, offset=0, captcha_key=captcha_key, captcha_sid=captcha_sid)
            captcha_key = -1
            print("good captcha")
            false_key = False
        else:
            First = api.board.getComments(group_id='30666517', topic_id='25736069', count=1, offset=0)
        total_comments = First["comments"][0]
        Last = api.board.getComments(group_id='30666517', topic_id='25736069', count=1, offset=total_comments - 1)
        can = Last["comments"][1]["from_id"] != 29629954
        if can:
            capcha_sleep = 1
            api.board.createComment(access_token=AT, group_id='30666517', topic_id='25736069', message="0x0" + hex(total_comments)[2:]
                + "\n\nЕсли вы хотите такого бота, напишите мне или Аристарху (на питоне или пхп соответственно)\n")
            print("new comment", "0x0" + hex(total_comments)[2:], total_comments / (2**20))
    except requests.exceptions.ReadTimeout:
        print("requests.exceptions.ReadTimeout")
        time.sleep(2)
    except IndexError:
        print("IndexError")
        time.sleep(2)
    except vk.exceptions.VkAPIError as error:
        if error.is_captcha_needed():
            if not false_key:
                false_key = True
                captcha_sid = error.captcha_sid
                captcha_key = [choice("qwertyuiopasdfghjklzxcvbnm1234567890") for _ in range(5)]
                time.sleep(10)
            else:
                false_key = False
                print("captcha_imgcha")
                print(error.captcha_img)
                auth_url = error.captcha_img
                webbrowser.open_new_tab(auth_url)
                captcha_sid = error.captcha_sid
                time.sleep(5)
                captcha_key = input("enter captcha ").rstrip()
                print(captcha_key)
                time.sleep(5)
        time.sleep(capcha_sleep)
        if capcha_sleep < 20:
            capcha_sleep += 1
