#include "utils.h"

int parse_command(char *command){
    char **pre_split = split(command, '\n'); //debug with nc command will have a '\n'; there is no need to add a '\n' in python
    char **result = split(pre_split[0],':');
    if (strcmp(result[0], "start") == 0)
    {
        printf("start!\n");
        STIM_START();
    }
    else if (strcmp(result[0], "stop") == 0)
    {
        printf("stop!\n");
        if (STIM_TASK_STATUS == 1)
        {
            STIM_STOP();
        }
    }else if(strcmp(result[0],"clr_wifi_cfg")==0){
        clear_wifi_config();
        printf("cleared\n");
    }else if(strcmp(result[0],"stim_amp")==0){
        if(result[1] == NULL){
            return STIM_AMP;
        }
        STIM_AMP = atoi(result[1]);
        return STIM_AMP;
    }
    else if (strcmp(result[0], "stim_type")==0)
    {
        if(result[1] == NULL){
            return STIM_TYPE;
        }
        STIM_TYPE = atoi(result[1]);
        return STIM_TYPE;
    }
    else if (strcmp(result[0], "anodic_cathodic")==0)
    {
        if(result[1] == NULL){
            return ANODIC_CATHODIC;
        }
        ANODIC_CATHODIC = atoi(result[1]);
        return ANODIC_CATHODIC;
    }
    else if (strcmp(result[0], "phase_one_time")==0)
    {
        if(result[1] == NULL){
            return PHASE_ONE_TIME;
        }
        PHASE_ONE_TIME = atoi(result[1]);
        return PHASE_ONE_TIME;
    }
    else if (strcmp(result[0], "inter_phase_gap")==0)
    {
        if(result[1] == NULL){
            return INTER_PHASE_GAP;
        }
        INTER_PHASE_GAP = atoi(result[1]);
        return INTER_PHASE_GAP;
    }
    else if (strcmp(result[0], "phase_two_time")==0)
    {
        if(result[1] == NULL){
            return PHASE_TWO_TIME;
        }
        PHASE_TWO_TIME = atoi(result[1]);
        return PHASE_TWO_TIME;
    }
    else if (strcmp(result[0], "inter_stim_delay")==0)
    {
        if(result[1] == NULL){
            return INTER_STIM_DELAY;
        }
        INTER_STIM_DELAY = atoi(result[1]);
        return INTER_STIM_DELAY;
    }
    else if (strcmp(result[0], "pulse_num")==0)
    {
        if(result[1] == NULL){
            return PULSE_NUM;
        }
        PULSE_NUM = atoi(result[1]);
        return PULSE_NUM;
    }
    else if (strcmp(result[0], "burst_num")==0)
    {
        if(result[1] == NULL){
            return BURST_NUM;
        }
        BURST_NUM = atoi(result[1]);
        return BURST_NUM;
    }
    else if (strcmp(result[0], "inter_burst_delay")==0)
    {
        if(result[1] == NULL){
            return INTER_BURST_DELAY;
        }
        INTER_BURST_DELAY = atoi(result[1]);
        return INTER_BURST_DELAY;
    }
    else if (strcmp(result[0], "ramp_up") == 0)
    {
        if(result[1] == NULL){
            return RAMP_UP;
        }
        RAMP_UP = atoi(result[1]);
        return RAMP_UP;
    }
    else if (strcmp(result[0], "short_electrode") == 0)
    {
        if(result[1] == NULL){
            return SHORT_ELECTRODE;
        }
        SHORT_ELECTRODE = atoi(result[1]);
        return SHORT_ELECTRODE;
    }
    else if (strcmp(result[0], "pulse_num_in_one_burst") == 0)
    {
        if(result[1] == NULL){
            return PULSE_NUM_IN_ONE_BURST;
        }
        PULSE_NUM_IN_ONE_BURST = atoi(result[1]);
        return PULSE_NUM_IN_ONE_BURST;
    }
    else if (strcmp(result[0], "enable_record") == 0)
    {
        if(result[1] == NULL){
            return ENABLE_RECORD;
        }
        ENABLE_RECORD = atoi(result[1]);
        return ENABLE_RECORD;
    }
    else if (strcmp(result[0], "record_offset") == 0)
    {
        if(result[1] == NULL){
            return RECORD_OFFSET;
        }
        RECORD_OFFSET = atoi(result[1]);
        return RECORD_OFFSET;
    }
    else if (strcmp(result[0], "debug_enable") == 0)
    {
        DEBUG_MODE_ENABLED = atoi(result[1]);
    }
    else if (strcmp(result[0], "dac_phase_one") == 0)
    {
        DAC_PHASE_ONE = atoi(result[1]);
    }
    else if (strcmp(result[0], "dac_phase_two") == 0)
    {
        DAC_PHASE_TWO = atoi(result[1]);
    }

    if(DEBUG_MODE_ENABLED){
        printf("***********************************************************\n");
        printf("%s and %s\n", ANODIC_CATHODIC ? "CATHODIC" : "ANODIC", STIM_TYPE ? "BURST" : "UNIFORM");
        printf("stim amp : %u   phase one time : %u    phase two time: %u\n", STIM_AMP, PHASE_ONE_TIME, PHASE_TWO_TIME);
        printf("inter phase gap : %u   inter stim delay : %u  pulse num : %u\n", INTER_PHASE_GAP, INTER_STIM_DELAY, PULSE_NUM);
        printf("pulse num in one burst : %u     burst num : %u    inter burst delay : %u\n", PULSE_NUM_IN_ONE_BURST,BURST_NUM, INTER_BURST_DELAY);
        printf("ramp up : %s\n",RAMP_UP?"yes":"no");
        printf("short electrode : %s\n",SHORT_ELECTRODE?"yes":"no");
        printf("recording : %s      recording start offset : %d\n", ENABLE_RECORD ? "yes" : "no", RECORD_OFFSET);
        printf("***********************************************************\n");
    }

    int x = 0;
    while(pre_split[x] != NULL){
        free(pre_split[x]);
        x++;
    }
    free(pre_split);

    x = 0;
    while(result[x] != NULL){
        free(result[x]);
        x++;
    }
    free(result);
    return -1;
}



char **split(const char *command, char splitter)
{
    char **result;
    int j, n = 0;
    int count = 1;
    int len = strlen(command);
    char tmp[len + 1];
    tmp[0] = '\0';

    for (int i = 0; i < len; ++i)
    {
        if (command[i] == splitter && command[i + 1] == '\0')
            continue;
        else if (command[i] == splitter && command[i + 1] != splitter)
            count++;
    }
    result = (char **)malloc((count + 1) * sizeof(char *));

    count = 0;
    for (int i = 0; i < len; ++i)
    {
        if (i == len - 1 && command[i] != splitter)
        {
            tmp[n++] = command[i];
            tmp[n] = '\0';
            j = strlen(tmp) + 1;
            result[count] = (char *)malloc(j * sizeof(char));
            strcpy(result[count++], tmp);
        }
        else if (command[i] == splitter)
        {
            j = strlen(tmp);
            if (j != 0)
            {
                tmp[n] = '\0';
                result[count] = (char *)malloc((j + 1) * sizeof(char));
                strcpy(result[count++], tmp);
                n = 0;
                tmp[0] = '\0';
            }
        }
        else
            tmp[n++] = command[i];
    }
    result[count] = NULL;
    return result;
}

void clear_wifi_config(){
    nvs_flash_init();
    nvs_handle_t nvs;
    nvs_open("wifiCreds", NVS_READWRITE, &nvs);
    nvs_erase_key(nvs,"ssid");
    nvs_erase_key(nvs,"pass");
    nvs_close(nvs);
}