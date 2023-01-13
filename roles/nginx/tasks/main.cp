---

- name: Install Nginx
  apt:
          name: nginx
          state: latest
  tags: nginx

  
- name: delete default nginx site
  file:
          path: /etc/nginx/sites-available/default
          state: absent
  notify: restart nginx

- name: copy index.php to site
  template:
          src: index.php
          dest: "/var/www/{{ http_host }}"
          mode: 0755
          owner: "{{ app_user }}"
          group: "{{ app_user }}"
  tags: nginx

- name: copy nginx site.conf
  template:
          src: site.conf
          dest: /etc/nginx/sites-available/
          owner: root
          group: root
          mode: '0644'

- name: enable new conf
  become: true
  shell: ln -s /etc/nginx/sites-available/site.conf /etc/nginx/sites-enabled/site.conf
  tags: nginx
  notify:
          - nginx service started
          - nginx service enabled          
