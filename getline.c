#include "shell.h"

/**
 * inputBuffer - Read input and handles command chaining.
 * @info: Parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of the length variable.
 * Return: Bytes read.
 */
ssize_t inputBuffer(info_t *info, char **buf, size_t *len)
{
	ssize_t bytesRead = 0;
       	size_t len_p = 0;

 	if (!*len) /* If nothing left in the buffer, fill it */
       	{
	       	free(*buf);
	       	*buf = NULL;
	       	signal(SIGINT, sigintHandler);

#if USE_GETLINE
	       	bytesRead = getline(buf, &len_p, stdin);
#else
	       	bytesRead = _getline(info, buf, &len_p);
#endif
	
		if (bytesRead > 0)
	       	{
		       	if ((*buf)[bytesRead - 1] == '\n')
		       	{
			       	(*buf)[bytesRead - 1] = '\0'; /* Remove trailing newline */
			       	bytesRead--;
		       	}
		       
			info->linecount_flag = 1;
		       	removeComments(*buf);
		       	buildHistoryList(info, *buf, info->histcount++);
		       
			/* Check if this is a command chain */
		       	if (_strchr(*buf, ';'))
		       	{
			       	*len = bytesRead;
			       	info->cmd_buf = buf;
		       	}
	       	}
       	}
       
	return bytesRead;
}

/**
 * getUserInput - Retrieve a line of input excluding the newline character.
 * @info: Parameter struct.
 * Return: Bytes read.
 */
ssize_t getUserInput(info_t *info)
{
       	static char *buf; /* The ';' command chain buffer */
       	static size_t i, j, len;
       	ssize_t bytesRead = 0;
       	char **buf_p = &(info->arg), *p;

	 _putchar(BUF_FLUSH);
	 bytesRead = inputBuffer(info, &buf, &len);

	 if (bytesRead == -1) /* EOF */
		 return -1;
	
	 if (len) /* We have commands left in the chain buffer */
	 {
		 j = i; /* Initialize new iterator to the current buf position */
		 p = buf + i; /* Get pointer for return */
		
		 checkChain(info, buf, &j, i, len);
		 while (j < len) /* Iterate to semicolon or end */
		 {
			 if (isChain(info, buf, &j))
				 break;
			 j++;
		 }
		
		 i = j + 1; /* Increment past nulled ';'' */
		 if (i >= len) /* Reached the end of the buffer? */
		 {
			 i = len = 0; /* Reset position and length */
			 info->cmd_buf_type = CMD_NORM;
		 }
		
		 *buf_p = p; /* Pass back pointer to the current command position */
		 return _strlen(p); /* Return the length of the current command */
	 }
	
	 *buf_p = buf; /* Not a chain, pass back buffer from _getline() */
	 return bytesRead; /* Return the length of the buffer from _getline() */
}

/**
 * readBuffer - Reads the buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buf, size_t *i)
{
       	ssize_t bytesRead = 0;
       
	if (*i)
	       	return 0;
       
	bytesRead = read(info->readfd, buf, READ_BUF_SIZE);
       
	if (bytesRead >= 0)
	       	*i = bytesRead;

 	return bytesRead;
}

/**
 * _getline - Gets next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of  pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 * Return: bytesRead.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
      	static char buf[READ_BUF_SIZE];
       	static size_t i, len;
       	size_t k;
       	ssize_t bytesRead = 0, totalBytesRead = 0;
       	char *p = NULL, *new_p = NULL, *c;
       
	p = *ptr;
       	if (p && length)
	       	totalBytesRead = *length;
	
	if (i == len)
	       	i = len = 0;
       
	bytesRead = readBuffer(info, buf, &len);

       	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
	 return -1;
	
	 c = _strchr(buf + i, '\n');
	 k = c ? 1 + (unsigned int)(c - buf) : len;
	 new_p = _realloc(p, totalBytesRead, totalBytesRead ? totalBytesRead + k : k + 1);
	
	 if (!new_p) /* MALLOC FAILURE! */
		 return p ? free(p), -1 : -1;
	
	 if (totalBytesRead)
		 _strncat(new_p, buf + i, k - i);
	 else
		 _strncpy(new_p, buf + i, k - i + 1);
	
	 totalBytesRead += k - i;
	 i = k;
	 p = new_p;

	 if (length)
		 *length = totalBytesRead;

	 *ptr = p;
	 return totalBytesRead;
}

/**
 * sigintHandler - Block Ctrl-C.
 * @sig_num: The signal number.
 * Return: void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
      	_puts("\n");
       	_puts("$ ");
       	_putchar(BUF_FLUSH);
}
