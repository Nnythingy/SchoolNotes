import requests
import json
import pandas
from bs4 import BeautifulSoup
import apisecrets
import songs

def lyrics_list_to_dict(lyrics_list, artist):
    #returns a dictionary of lyrics
    lyrics_dict = {}
    keyname = ""
    verse_number = 1
    for i in lyrics_list:
        # print(i)
        if "Lyrics" in i:
            #title of song
            lyrics_dict["Title"] = i
        elif "[" in i:
            #handle main sections in lyrics
            words = i.split(' ')
            category = words[0].strip("[]: ") #remove symbols
            if "verse" in category.lower():
                #for songs with multiple artists verse sections includes who is singing
                #thus removing the artists and changing labels back to verse #number if len(words) != 1:
                    i = category + " " +str(verse_number)
                    verse_number += 1
            i = category
            if i not in lyrics_dict.keys():
                #checking if key already exist, if no create a new count key
                lyrics_dict[i] = ''
                lyrics_dict[f'{i}_count'] = 0
            keyname = i
            lyrics_dict[f'{i}_count'] += 1
        else:
            try:
                if i not in lyrics_dict[keyname]:
                    lyrics_dict[keyname] = lyrics_dict[keyname].strip() + f" {i}"
            except:
                continue
    return lyrics_dict


def scrape_lyrics(url, song, artist):
    # Function to search for a song and get its lyrics
    print(url + "\n")
    page = requests.get(url)
    html = BeautifulSoup(page.text, 'html.parser')
    unclean_text = html.find("div", id="lyrics-root").findAll(text=True)
    try:
        start_index = unclean_text.index(f'{song} Lyrics')
    except:
        start_index = 0
    try:
        end_index = unclean_text.index('[Music Video]') - 1
    except:
        end_index = -2
    return lyrics_list_to_dict(unclean_text[start_index:end_index], artist)

def get_lyrics(song_title:str, artist_name:str, complete_search:bool):
    #returns a dictionary of lyrics
    GENIUS_API_TOKEN = apisecrets.genius_token
    base_url = 'https://api.genius.com'
    search_url = f'{base_url}/search'
    headers = {
        'Authorization': f'Bearer {GENIUS_API_TOKEN}',
    }
    
    # Search for the song
    params = {
        #add in the artist name to the search if requested
        'q': f'{song_title} {artist_name if complete_search else ""}'
    }
    response = requests.get(search_url, headers=headers, params=params)
    if response.status_code == 200:
        # Extract the song URL
        search_results = response.json()
        hits = search_results['response']['hits']
        if hits:
            for i in range(len(hits)):
                artists = artist_name.replace("&", "").split()
                for name in artists:
                    if name.lower() in hits[i]['result']['primary_artist']['name'].lower():
                        print(name, hits[i]['result']['primary_artist']['name'].lower())
                        song_url = hits[i]['result']['url']
                        return scrape_lyrics(song_url, song_title, artist_name)
            #if no matching songs are found with only the song title, then re run the search with the artist name as well
            #this is unfortunately required because some songs have more accurate search results without the artist name
            if complete_search:
                return {}
            else:
                get_lyrics(song_title, artist_name, True)
    return {}

lyrics = {}

for k, v in songs.tiktok_50.items():
    song_title = k
    artist = v
    print (k, v)
    lyrics[k] = get_lyrics(song_title, artist, False)

df = pandas.DataFrame(data=lyrics)
df = (df.T)
df.to_excel('tiktok50.xlsx')

for k, v in songs.billboard_50.items():
    song_title = k
    artist = v
    print (k, v)
    lyrics[k] = get_lyrics(song_title, artist, False)

df = pandas.DataFrame(data=lyrics)
df = (df.T)
df.to_excel('billboard50.xlsx')

# song_title = 'My Love Mine All Mine'
# artist = 'Mitski'
# lyrics.update(get_lyrics(song_title, artist))
# print(lyrics)
