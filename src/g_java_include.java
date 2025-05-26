import java.io.*;
import java.time.*;
import java.time.format.DateTimeFormatter;
import java.util.*;

class list<T>{

    public list(T t){
        this.dummy = t;
        this.array = new ArrayList<>();
        write_log(this.current_time() + " : Initialized list<T> [with T = " + 
                  ((Object)(this.dummy)).getClass().getName() + ", [Hash = " + ((Object)(this)).hashCode() + "]");
    }

    public list(T[] array){
        this.dummy = array[0];
        this.array = new ArrayList<>();
        if(array.length != 0)
            for(int index = 0; index != array.length; ++index)
                this.array.add(array[index]);
        write_log(this.current_time() + " : Initialized list<T> [with T = " + 
                  ((Object)(this.dummy)).getClass().getName() + ", [Hash = " + ((Object)(this)).hashCode() + "]\n\tAdded " + array.length + " elements of T, in construction.");
    }

    public void append(T[] array){
        if(array.length != 1){
            for(int index = 0; index != array.length; ++index)
                this.array.add(array[index]);
            write_log(this.current_time() + " : Appended " + array.length + " elements to : " + ((Object)(this)).hashCode());
        }
    }

    public void close(){
        write_log(this.current_time() + " : De-Instantiating list<T> [Hash = " + ((Object)(this)).hashCode() + ']');
    }
    

    private final String log_file_name = "list.log";
    private List<T> array;
    private T dummy;
    private static int write_count = 0;

    private long write_log(final String message){
        try(BufferedWriter writer = new BufferedWriter(new FileWriter(this.log_file_name, true))){
            try {
                if(write_count == 0)
                    writer.write('\n');
                writer.write(message + '\n');
                write_count++;
            } catch (IOException e) {}
        }catch(IOException e){
            System.out.println("Error : " + e.getMessage());
        }
        return message.length();
    }

    private String current_time(){
        final LocalDateTime time = LocalDateTime.now();
        DateTimeFormatter format = DateTimeFormatter.ofPattern("yyyy-MM-dd - HH:mm:ss");
        return time.format(format);
    }

    public static void main(String[] args) {
        list<String> list = new list<>("");
        list<String> s_list = new list<>(new String[]{"rakshit", "24MEI10086", "K1009"});

        list.append(new String[]{"rakshit", "24MEI10086", "K19"});

        list.close();
        s_list.close();
    }
}