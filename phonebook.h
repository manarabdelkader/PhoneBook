#ifndef PHONEBOOK_H_INCLUDED
#define PHONEBOOK_H_INCLUDED
int load();
int searchcontact(int x);
void addcontact();
void deletecontact();
void modifycontact(int x);
void printcontacts();
void sortbydob();
void sortbylname();
void savecontact();
int ValidDateofBirth (int D, int M, int Y);
int ValidName(char *name);
int ValidPhoneNum(char *phonenumber);
int ValidEmail(char *email);
#endif // PHONEBOOK_H_INCLUDED

