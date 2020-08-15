#!/usr/bin/env python3
import random

def add_people(): # let user add people attending
    x = []
    tt = {}
    nop = 0
    while True:
        print('Enter name; when done enter done')
        name = input()
        if name == 'done':
            break
        else:
            x.append(name)
            tt[name] = len(name.split())
            nop += len(name.split())
    return x, tt, nop


def distribution(n,sb): # make an array that represents the number of people in each group, depending on the number of attendance n
    # this has a minimum attendance of 6. For 5 people or less it is assumed that the group merges into one
    if sb == 'big':
        starting_dist = [4,4,4]
        max_person = 5
        dec_ind = 3
    elif sb =='small':
        starting_dist = [3,3]
        max_person = 4
        dec_ind = 2
    group_dist = starting_dist
    n -= sum(group_dist)
    while n>0:
        for x in range(len(group_dist)):
            if group_dist[x] < max_person:
                group_dist[x] += 1
                break
        else:
            for y in range(dec_ind):
                group_dist[-(y+1)] -= 1
            group_dist.append(max_person-1)
        n -= 1
    return group_dist

def print_instruction():
    print("Hi! Isi dengan nama peserta, jika ada peserta yang harus bersama karena satu skype atau sebagainya, "
          "tolong insert di satu entry dengan seperator spasi. ")
    print("Inget, kalau pakai seperator itu dianggep dua orang *jangan koh john tapi pakai KohJohn*")

def roll(group_dist,tt,subgroup_list):
    for x in group_dist:
        #for each group,
        while x>0:
        #pick one from orang_list
            chosen = random.choice(subgroup_list)
            while tt[chosen] > x: #the number of people in this subgroup might be more than needed to be added to this group
                #if that's the case, pick another random subgroup
                chosen = random.choice(subgroup_list) #repick
            subgroup_list.remove(chosen) #this subgroup cannot be picked again
            x -= tt[chosen]
            print(chosen, end = ' ')
        print()


print_instruction()
while(True):
    print('Small group or big group?')
    in_small = input()
    if in_small == 'small' or in_small == 'big':
        sb = in_small
        break;
    else:
        print('Wrong input!')

#orang_list - list of attendants without seperation, a member of this list may contain more than one attendant due to joint skype/zoom
#tt - dict of number of persons in each member of orang_list
#jumlah_orang - number of total attendants (not len(orang_list)!!!)
subgroup_list,tt,number_people = add_people()

#group_dist - list of number of attendants in each group
group_dist = distribution(number_people,sb)


while(True):
    roll(group_dist.copy(),tt,subgroup_list.copy())
    print('Reroll? (y/n)')
    rer = input()
    if rer == 'y':
        continue
    elif rer =='n':
        break
    else:
        print('what? rerolling...')
        
