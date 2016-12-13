


int array_length, file_length;
int *array_master;
FILE *freader;

int *read_file(char *fname) {
	freader = fopen(fname, "rt");
	int bufsize = file_length;
	char line[80];
	int integer;
	int index = 0;
	int *input = malloc(bufsize * sizeof(int));

	while(fgets(line, 80, freader) != NULL) {
		sscanf(line, "%d", &integer);
		input[index] = integer;
		++index;
		++array_length;
	}

	fclose(freader);
	return input;
}

int read_length(char *fname) {
	freader = fopen(fname, "rt");
	char line[80];
	int file_length = 0;

	while(fgets(line, 80, freader) != NULL) {
		file_length += 1;
	}
	return file_length;
}

void merge(int arr[], int left, int middle, int right) {
	int i, j, k;
	int half1 = middle - left + 1;
	int half2 = right - middle;

	int first[half1], second[half2];

	for(i = 0; i < half1; i++) {
		first[i] = arr[left + i];
	}

	for(j = 0; j < half2; j++) {
		second[j] = arr[middle + 1 + j];
	}

	i = 0;
	j = 0;
	k = left;

	while(i < half1 && j < half2) {
		if(first[i] <= second[j]) {
			arr[k] = first[i];
			++i;
		} else {
			arr[k] = second[j];
			j++;
		}
		k++;
	}

	while(i < half1) {
		arr[k] = first[i];
		i++;
		k++;
	}

	while(j < half2) {
		arr[k] = second[j];
		j++;
		k++;
	}
}

void merge_sort(void *arg) {
	int *arr = array_master;
	int *argu = (int *)arg;
	int l = argu[0];
	int r = argu[1];

	if(l < r) {
		pthread_t tid1;
		pthread_t tid2;

		int arg1[2];
		int arg2[2];

		int middle;
		middle = (l + (r - 1)) / 2;
		arg1[0] = l;
		arg1[1] = middle;
		arg2[0] = middle + 1;
		arg2[1] = r;

		pthread_create(&tid1, NULL, merge_sort, arg1);
		pthread_create(&tid2, NULL, merge_sort, arg2);

		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);

		merge(arr, l, middle, r);
		pthread_exit(0);
	}
}

int main(int argc, char *argv[]) {
	char *fname = argv[1];

	file_length = read_length(fname);

	array_master = read_file(fname);

	int arg[2];
	arg[0] = 0;
	arg[1] = file_length;

	pthread_t tid;
	pthread_create(&tid, NULL, merge_sort, arg);

	pthread_join(tid, NULL);

	int j;
	for(j = 0; j < array_length; j++) {
		if(j == array_length - 1) {
			printf("%d\n", array_master[j]);
		} else {
			printf("%d, ", array_master[j]);
		}
	}

	return 0;
}