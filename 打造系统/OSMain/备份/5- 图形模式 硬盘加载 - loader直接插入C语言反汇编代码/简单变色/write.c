void main()
{
	int i; /* �ϐ��錾�Bi�Ƃ����ϐ��́A32�r�b�g�̐����^ */
	char *p; /* p�Ƃ����ϐ��́ABYTE [...]�p�̔Ԓn */

	p = (char *) 0xa0000; /* �Ԓn���� */

	for (i = 0; i <= 0xffff; i++) {
		*(p + i) = i & 0x0f;
	}

	while(1);
}
