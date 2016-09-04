 #!/usr/bin/python2.7
# Filename: get_boot_offset.py


MODEM_MAGIC = "SCI1"
MODEM_HDR_SIZE = 12 #size of a block
MODEM_IMG_HDR = 0x1
MODEM_LAST_HDR = 0x100
MODEM_SHA1_HDR = 0x400
MODEM_SHA1_SIZE = 20



def get_boot_offset(ifile=None):
	''' file format is such as out/target/product/.../SC9600_whale_cr5_v110.bin '''
	if type(ifile) != str:
		print "invalid input parameter"
		return None

	try:
		fdin = file(ifile, 'r')
		print ifile, " is opened"
		modem_magic = fdin.read(MODEM_HDR_SIZE)
		if modem_magic.__len__() != MODEM_HDR_SIZE
			print "fdin.read error -1 ", modem_magic.__len__()
			fdin.close()
			return None
		if modem_magic.__eq__(MODEM_MAGIC) is False:
			print modem_magic, "!=", MODEM_MAGIC
			fdin.close()
			return None
		hdr_buf = fdin.read(MODEM_HDR_SIZE << 3)
		if hdr_buf.__len__() != MODEM_HDR_SIZE << 3:
			print "fdin.read error -2 ", hdr_buf.__len__()
			fdin.close()
			return None
		hdr_ptr = 0
		result = 0 # 0:OK, 1:not find, 2:some error occur
		while hdr_buf.find(str(MODEM_IMG_HDR), hdr_ptr, hdr_ptr + MODEM_HDR_SIZE) != 0:#hdr_buf[hdr_ptr:hdr_ptr + 4].__eq__(str(MODEM_IMG_HDR)) or int(hdr_buf[hdr_ptr:hdr_ptr + 4]) == MODEM_IMG_HDR
			hdr_ptr += MODEM_HDR_SIZE
			if hdr_ptr == MODEM_HDR_SIZE << 3:
				result = 1
				break
			if hdr_buf.find(str(MODEM_LAST_HDR), hdr_ptr, hdr_ptr + MODEM_HDR_SIZE) == 0:
				result = 2
				break
		if result == 0:
			offset = int(hdr_buf[hdr_ptr + 4:hdr_ptr + 8])
			if hdr_buf[hdr_ptr + 0:hdr_ptr + 4].__eq__(str(MODEM_SHA1_HDR)):#int(hdr_buf[hdr_ptr + 0:hdr_ptr + 4]) == MODEM_SHA1_HDR
				offset += MODEM_SHA1_SIZE
				img_len = int(hdr_buf[hdr_ptr + 8:hdr_ptr + 12])
		else:
			print "data_block_header_t error"
			fdin.close()
			return None
		fdin.seek(offset, 0)
		data = fdin.read(img_len)
		if data.__len__() != img_len:
			print "fdin.read error -3 ", data.__len__()
			fdin.close()
			return None

	except Exception,e:
		print "fdin - error is triggered"
		print "%s:%s" % (Exception, e)
		fdin.close()
		return None
	finally:
		print ifile, " is closed"
		fdin.close()

	tmp_name = ifile.split('.')
	filename = tmp_name[0] + '-new' + tmp_name[1]

	try:
		fdout = file(filename, "w")
		fdout.write(data)

	except Exception,e:
		print "fdout - error is triggered"
		print "%s:%s" % (Exception, e)
		fdout.close()
		return None
	finally:
		print filename, " is closed"
		fdin.close()

	return filename



if __name__ == '__main__':
	print 'please call function get_boot_offset directly'

