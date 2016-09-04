
#define MODEM_MAGIC		"SCI1"
#define MODEM_HDR_SIZE		12 //size of a block
#define MODEM_IMG_HDR		0x1
#define MODEM_LAST_HDR		0x100
#define MODEM_SHA1_HDR		0x400
#define MODEM_SHA1_SIZE		20
#define FILE_NAME_MAX		1024

typedef struct {
	unsigned int type_flags;
	unsigned int offset;
	unsigned int length;
} data_block_header_t;

char* get_boot_offset(char *file)
{
	// file format is such as out/target/product/.../SC9600_whale_cr5_v110.bin

	int fdin = -1;
	int fdout = -1;
	unsigned int offset = 0;
	unsigned char hdr_buf[MODEM_HDR_SIZE << 3] = {0};
	unsigned char read_len = 0;
	unsigned char img_len = 0;
	unsigned char result = 0; // 0:OK, 1:not find, 2:some error occur
	data_block_header_t* hdr_ptr = NULL;
	unsigned char modem_magic[MODEM_HDR_SIZE];

	char suffix[10] = "0";
	char flag = '.';
	char *namesuffix = "-new";
	char *start = NULL;
	char *end = NULL;
	unsigned char *data = NULL;
	char *filename = NULL;


	fdin = open(file, O_RDONLY, 0);
	if(fdin < 0) {
		goto fail;
	}

	read_len = read(fdin, modem_magic, MODEM_HDR_SIZE);
	if(read_len != MODEM_HDR_SIZE)	{ 
		goto fail;
	}

	if(memcmp(modem_magic, MODEM_MAGIC, sizeof(MODEM_MAGIC))) {
		goto fail;
	}

	
	read_len = read(fdin, hdr_buf, sizeof(hdr_buf));
	if(read_len != sizeof(hdr_buf))	{ 
		goto fail;
	}

	hdr_ptr = (data_block_header_t*)hdr_buf;

	while(!(hdr_ptr->type_flags & MODEM_IMG_HDR)) {
		hdr_ptr++;
		if(read_len == ((uint8_t*)hdr_ptr - hdr_buf)) {
			result = 1;
			break;
		}

		if(hdr_ptr->type_flags & MODEM_LAST_HDR) {
			result = 2;
			break;
		}
	};


	if(!result) {
		offset = hdr_ptr->offset;
		if(hdr_ptr->type_flags & MODEM_SHA1_HDR) {
			offset += MODEM_SHA1_SIZE;
		}
		img_len = hdr_ptr->length;
	} else {
		goto fail;
	}

	if (lseek(fdin, offset, SEEK_SET) != (offset)) {
		goto fail;
	}
	
	data = (unsigned char*) malloc(img_len);
	if(data == 0) {
		goto fail;
	}

	memset(data, 0, psz);
	read_len = read(fdin, data, img_len);
	if (read_len != img_len) {
		goto fail;
	}

	filename = (char*) malloc(FILE_NAME_MAX);
	if(filename == 0) {
		goto fail;
	}
	
	memset(filename, 0, FILE_NAME_MAX);
	strcpy(filename,file);

	start = file;
	end = strrchr(start,flag);

	memcpy(suffix,end,strlen(end)+1);
	filename[end-start] = '\0';
	strcat(filename,namesuffix);
	strcat(filename,suffix);

	fdout = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fdout > 0) {
		if (write(fdout, data, img_len) != img_len) {
			free(filename);
			filename = NULL;	
			goto fail;
		}
	} else {
		free(filename);
		filename = NULL;
		goto fail;
	}

fail:
	if (data) {
		free(data);
		data = NULL;
	}
	if(fdin >= 0)
		close(fdin);
	if(fdout >= 0)
		close(fdout);
	return filename;
}

